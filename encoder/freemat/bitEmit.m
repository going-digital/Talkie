% Talkie library
% Copyright 2011 Peter Knight
% This code is released under GPLv2 license.
%
% Emit a parameter as bits

function bitEmit(val,bits)
    bitpos = 2^(bits-1);
    for b = 1:bits
        if bitand(val,bitpos)
            printf('1');
        else
            printf('0');
        end
        val = val*2;
    end
