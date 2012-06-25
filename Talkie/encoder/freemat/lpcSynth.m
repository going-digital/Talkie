% Talkie library
% Copyright 2011 Peter Knight
% This code is released under GPLv2 license.
%
% Synthesise model parameters

function samples=lpcSynth(pitch,energy,coefficients,length,poles,sampleRate)
    samples = zeros(1,length);
    u = zeros(1,poles+1);
    x = zeros(1,poles+1);
    
    % Generate excitation
    if pitch>0
        % Voiced
        excite = zeros(1,length);
        for a=1:(sampleRate/pitch):length
            excite(floor(a)) = 1;
        end
        %excite = mod((1:length)*pitch/sampleRate,1)-0.5;
    else
        % Unvoiced
        excite = rand(1,length)-0.5;
    end
    excite = excite * energy;
    
    % Run through filter
    for s=1:length
        u(poles+1) = excite(s);
        for t=poles:-1:1
            u(t) = u(t+1) - coefficients(t+1)*x(t);
        end
        for v=poles-1:-1:1
            x(v+1) = x(v) + coefficients(v+1)*u(v);
        end
        if x(1) > 1
            x(1) = 1;
        end
        if x(1) < -1
            x(1) = -1;
        end
        x(1) = u(1);
        samples(s) = u(1);
    end
    samples = samples';