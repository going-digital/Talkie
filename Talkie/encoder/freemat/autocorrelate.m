% Talkie library
% Copyright 2011 Peter Knight
% This code is released under GPLv2 license.
%
% Calculate autocorrelation of speech segment

function r = autocorrelate(w,len)
    r = zeros(1,len);
    wlen = length(w);
    for n=1:len
        r(n) = sum( w(1:wlen-n+1) .* w(n:wlen) );
    end
