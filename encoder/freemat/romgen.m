% Talkie library
% Copyright 2011 Peter Knight
% This code is released under GPLv2 license.
%
% Convert model parameter mapping into bitstream for ROM

frames = csvread('tomsDinerStream.csv');
lastFrame = [-1,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1]; % Jumk frame

repeatThreshold = 4;

silentFrames = 0;
repeatFrames = 0;
unvoicedFrames = 0;
voicedFrames = 0;

numFrames = size(frames)(1);

for f = 1:numFrames;
    frame = frames(f,:);
    % Is this a silent frame?
    if frame(1) < 1
        % Emit a silent frame
        bitEmit(0,4);
        silentFrames = silentFrames + 1;
        lastFrame = [0,0,0,0,0,0,0,0,0,0,0,0,0];
    else
        bitEmit(frame(1),4);
        coefficientDelta = sum(abs(frame(4:13)-lastFrame(4:13)));
        if coefficientDelta <= repeatThreshold
            % Emit a repeat frame
            bitEmit(1,1);
            bitEmit(frame(3),6);
            repeatFrames = repeatFrames + 1;
            lastFrame(1) = frame(1);
            lastFrame(3) = frame(3);
        else
            bitEmit(0,1);
            bitEmit(frame(3),6);
            bitEmit(frame(4),5);
            bitEmit(frame(5),5);
            bitEmit(frame(6),4);
            bitEmit(frame(7),4);
            if frame(3) < 1
                % Emit an unvoiced frame
                unvoicedFrames = unvoicedFrames + 1;
                lastFrame = frame;
            else
                % Emit a voiced frame
                bitEmit(frame(8),4);
                bitEmit(frame(9),4);
                bitEmit(frame(10),4);
                bitEmit(frame(11),3);
                bitEmit(frame(12),3);
                bitEmit(frame(13),3);

                voicedFrames = voicedFrames + 1;
                lastFrame = frame;
            end
        end
    end
end

% Emit a stop frame
bitEmit(15,4);

printf('Frames:\n%d V, %d U, %d R, %d S\n',voicedFrames,unvoicedFrames,repeatFrames,silentFrames);
romSize = 50*voicedFrames + 29*unvoicedFrames + 11*repeatFrames + 4*silentFrames;
printf('Rom size %d bits\n',romSize);

% Output from this needs to be grouped into groups of 8 bits.
% LSB of byte is the first bit to be decoded.
% Then needs to be packaged up as a C snippet for inclusion in the libary.