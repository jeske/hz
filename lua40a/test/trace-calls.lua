-- trace calls
-- NOT CURRENTLY WORKING :-(

T={level=0,name="(no name)",source="(no source)"}

function indent(level)
 return level.." "..format("%"..level.."s","")
end

function linehook(line)
 if T.source ==nil then return end
 if T.line==nil then
  local x=getlocal(2)
  write(indent(T.level),T.name,"(")
  foreach(x,function(i,v)
   write(i,"=")
   if tag(v)==tag("") then
    write(format("%q",v))
   else
    write(tostring(v))
   end
   write(",")
   end)
  write(")\n")
 end
 T.line=line
end

function callhook(func)
 error""
 read()
 local t=getstack(2) or getstack(1)
if t==nil then print"t is NIL" return end
-- foreach(t,print)
foreach(t,print)
 if t.kind=="chunk" then
  if func then
   write("BEGIN ",t.source)
  else
   write("END ",t.source)
  end
 else
  if func then
   write("CALL ")
  else
   write("RET ")
  end
  write(t.name,"\t",t.source or t.kind)
 end
 if t.current then write(":",t.current) end
 write("\n")
 --read()
do return end
foreach(t,print)
 if func==nil then
  if T.prev then T=T.prev end
 else
  local t=funcinfo(func)
  T={level=T.level+1,source=t.source,prev=T}
  if t.kind=="chunk" then
   T.name=t.source
  else
   if t.where=="global" then T.name=t.name else T.name=t.name.." tag method" end
  end
 end
end

--setlinehook(linehook)
setcallhook(callhook)
