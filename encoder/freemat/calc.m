% Talkie library
% Copyright 2011 Peter Knight
% This code is released under GPLv2 license.
%
% Main LPC mapping code.
% Converts WAV file into LPC model parameters.

clear

params = [];

% LPC10 encoder

% Read source file
[a,sampleRate, bitDepth] = wavread('TomsDiner8.wav');

b=a.*0; % Output buffer, matching size

% LPC10 frame is 25ms at 8000Hz
frameTime = 0.025;

frameSamples = sampleRate * frameTime;
W = 2*frameSamples;  % Window is twice as long as frame, to allow for windowing overlaps

% Precalculate hanning window, length 2 frames
hannWindow = transpose(0.5*(1-cos(2*pi*(0:(W-1))/(W-1))));

% Precalculate phases for 1Hz
phase = (1:W)*2*pi/sampleRate;

lpcOrder=10;

lena = length(a);
for frameStart = 1:W/2:(lena-W)

    % Window chunk of input
    frameChunk = a(frameStart:(frameStart+W-1),1);
    frameWindowed = (frameChunk .* hannWindow);

    % Measure energy
    frameEnergy = sqrt(mean(frameWindowed.*frameWindowed));

    % Measure pitch
    pitch = 235; % Mid point of Suzanne Vega's pitch range
    [pitch,pitchScore] = pitchRefine(frameWindowed,pitch,100,sampleRate);
    [pitch,pitchScore] = pitchRefine(frameWindowed,pitch,30,sampleRate);
    [pitch,pitchScore] = pitchRefine(frameWindowed,pitch,10,sampleRate);
    [pitch,pitchScore] = pitchRefine(frameWindowed,pitch,3,sampleRate);

    % Consonant detection
    if (pitchScore/frameEnergy > 0.1)
        isVoiced = 1;
    else
        isVoiced = 0;
        pitch = 0;
    end
    
    % Calculate LPC coefficients
    r = autocorrelate(frameWindowed,lpcOrder+1);
    [k,g] = levinsonDurbin(r,lpcOrder);
    if isVoiced==0
        g = 0.1*g;
    end
    
    [frameStart/lena,g]  % Show status

    % Quantise to match bit coding
    [pitch,g,k,frameBits] = lpcQuantise(pitch,g,k);
    params = vertcat(params,frameBits);
    
    % Synthesise from parameters
    d = lpcSynth(pitch,g,k,W,lpcOrder,sampleRate);
    d = d .* hannWindow;

    % Write back pitch to output wav
    b(frameStart:(frameStart+2*frameSamples-1)) = b(frameStart:(frameStart+2*frameSamples-1)) + d;

end
b = transpose(b);
wavwrite(b,8000,16,'TomsDinerPitch.wav');
csvwrite('tomsDinerStream.csv',params);
