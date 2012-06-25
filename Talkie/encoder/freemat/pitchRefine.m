% Talkie library
% Copyright 2011 Peter Knight
% This code is released under GPLv2 license.
%
% Home in on best fit pitch

function [pitch,score] = pitchRefine(w,pitchGuess,pitchRange,sampleRate)
    score = 0;
    phase = (1:length(w))*2*pi/sampleRate;
    for (newGuess = pitchGuess-pitchRange:pitchRange/10:pitchGuess+pitchRange)
        signal = exp(i*(newGuess*phase))';
        pitchScore = abs(mean(w .* signal));
        if (pitchScore > score)
            score = pitchScore;
            pitch = newGuess;
        end
    end
