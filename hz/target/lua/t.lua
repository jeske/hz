$debug
-- init.lua
-- 
-- game initialization code...
--

-- collectgarbage(1000);

-- first comes preloaded functions

 function printGlobalVariables ()
 local i, v = nextvar(nil)
  while i do
    print("["..i..", "..type(v).."]")
    i, v = nextvar(i)
  end
end

dofile("util.lua");

function printTables(a_table, owner,tabspace)
	local i,v = next(a_table,nil);
	local count = 0;

	if (owner ~= a_table) then

		if (owner == nil) then
			owner = a_table;
			tabspace = "+";
		end
		
		print(tabspace..tostring(a_table));

		while i do
			if (type(v) == "table") then
				print(tabspace.."  ["..type(i).."] ".. i .. " => [TABLE]");
				printTables(v,owner,tabspace.."    ");
			else 
				print(tabspace.."  ["..type(i).."]: "..i.." = ["..type(a_table[i]).."] ".. tostring(a_table[i]));
			end

			i,v = next(a_table,i)
			count = count + 1;
		end

		if (count == 1) then
			print(tabspace.."1 entry.");
		else
			print(tabspace .. count .. " entries.");
		end

	end

end

function printTable(a_table)
	local i,v = next(a_table,nil)
	local count = 0;

	print(a_table);
	while i do
		print("  ["..type(i).."]: "..i.." = ["..type(v).."] ".. tostring(a_table[i]))
		i,v = next(a_table,i)
		count = count + 1;
	end
	if (count == 1) then
		print("1 entry.");
	else 
		print(count .. " entries.");
	end
end

function clone (t)           -- t is a table
  local new_t = {}           -- create a new table
  local i, v = next(t, nil)  -- i is an index of t, v = t[i]
  while i do
    new_t[i] = v
    i, v = next(t, i)        -- get next index
  end
  return new_t
end

function trim(s)
  local _, i = strfind(s, '^ *')
  local f, __ = strfind(s, ' *$')
  return strsub(s, i+1, f-1)
end

-- this is for our basic proto-object inheritence

function Index (t,f)
  if f == 'parent' then  -- to avoid loop
    return OldIndex(t,f)
  end
  local p = t.parent
  if type(p) == 'table' then
    return p[f]
  else
    return OldIndex(t,f)
  end
end

OldIndex = settagmethod(tag({}),"index", Index)

