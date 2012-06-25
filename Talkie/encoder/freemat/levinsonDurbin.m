% Talkie library
% Copyright 2011 Peter Knight
% This code is released under GPLv2 license.
%
% Calculate LPC reflection coefficients

function [k,g] = levinsonDurbin(r,poles)
    k(1)=1;
    a=zeros(1,poles+1);
    at=zeros(1,poles+1);
    e=r(1);
    for s=1:poles
        k(s+1)=-r(s+1);
        for t=1:s-1
            at(t+1) = a(t+1);
            k(s+1) = k(s+1) - a(t+1) * r(s-t+1);
        end
        if abs(e)<eps
            e=0;
            break
        end
        k(s+1) = k(s+1) / e;
        a(s+1) = k(s+1);
        for u = 1:s-1
            a(u+1) = at(u+1) + k(s+1) * at(s-u+1);
        end
        e = e * (1-k(s+1)*k(s+1));
    end
    if e<eps
        e=0;
    end
    g = sqrt(e);