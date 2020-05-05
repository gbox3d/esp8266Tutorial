## Wiering

CLK<---> GPIO14  (d5)  
DIN<----> GPIO13  (d7)  
CS <----> GPIO15<-5k Ohm-> GND  (d8)   

## 참고 
https://frightanic.com/iot/nodemcu-max7219-8x8-led-matrix-display/  

```text
@TheSkor, Michael, out of interest you could write your Lua to be a lot more runtime efficient. For example in the case of drawPixel() using locals as upvalues and exploiting the fact that tables are passed by reference and only cascading changed updates, you'd end up with something like

function M.drawPixel(x,y,z)
  y = y + 1;
  local Mdy = (z == 0 and bitclr or bitset) (Md[y],x)
  Md[y] = Mdy
  spisend(1,y,Mdy)
end
where bitclr, bitset, spisend, Md are top-scoped local caches of bit.clr, etc. Run both sets of source through luac to see what I mean.
```