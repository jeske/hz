$debug
print("Util.lua!!!");


function printGlobalVariables2()
	local i;
        local scrwidth = 80; -- screen width
        local maxwidth = 0;
        local formatstring;

        -- first found out the max function name width

        i = nextvar(nil);
	while (i) do
	  if (type(getglobal(i)) == "function") then
		maxwidth = max(maxwidth,strlen(tostring(i)));
          end
           i = nextvar(i);
        end

        maxwidth = maxwidth + 2;

        local numcols = floor(scrwidth / maxwidth);
        local curcol = 0;

	formatstring = format("%%%ds  ",maxwidth);

        -- next column print all the function names

        i = nextvar(nil);
	while (i) do
	  if (type(getglobal(i)) == "function") then
		write(format(formatstring,tostring(i)));
                curcol = curcol + 1;
                if (curcol >= numcols) then
                   curcol = 0;
                   write("\n");
                end
          end
           i = nextvar(i);
        end

        

        write("\n");

	-- next, print out the variables:

	i = nextvar(nil);
 	while (i) do
 	  if (type(getglobal(i)) ~= "function") then
                 if (type(getglobal(i)) == "string") then
              	   write(format("%25s = '%25s' %10s\n", tostring(i), 
			tostring(getglobal(i)), 
			type(getglobal(i))));
                 elseif (type(getglobal(i)) == "number") then
              	   write(format("%25s = %25s %10s\n", tostring(i), 
			tostring(getglobal(i)), 
			type(getglobal(i))));
                 else -- who knows what type it is, just print it...
             	   write(format("%25s = '%25s' %10s\n", tostring(i), 
			tostring(getglobal(i)), 
			type(getglobal(i))));
                 end;
          end
          i = nextvar(i);
        end

end

function printTables(a_table, owner,tabspace)
	local i,v = next(a_table,nil);
	local count = 0;

    local formatIndex = function(index,tabspace)
	    if (type(index) == 'string') then
		   return (tabspace .. "'"..index.."'");
		else
		   return (tabspace .. tostring(index));
		end
	end

	if (owner ~= a_table) then

		if (owner == nil) then
			owner = a_table;
			tabspace = " ";
		end
		
		-- print(tabspace..tostring(a_table));

		while i do
			if (type(v) == "table") then
				print("+" .. formatIndex(i,tabspace) .. "=> ".. tostring(v));
				printTables(v,owner,tabspace.."    ");
			elseif (type(v) == "function") then

				print(tabspace .. tostring(i).."();      " .. tostring(v));
			else
				print(formatIndex(i,tabspace) .. "= ["..type(a_table[i]).."] ".. tostring(a_table[i]));
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

function ProtoIndex (t,f)
  if f == 'parent' then  -- to avoid loop
    if (OldIndex) then
		return OldIndex(t,f)
	else
		return nil;
	end
  end
  local p = t.parent
  if type(p) == 'table' then
    return p[f]
  else
    if (OldIndex) then
		return OldIndex(t,f)
	else
	    return nil;
	end
  end
end

-- this is more advanced inheritence

function AdvProtoIndex (t,f)
  
  if (f == '_parents') or (f == '_methodcache') then -- to avoid loop
    if (OldIndex) then
	    return OldIndex(t,f)
	else
		return nil;
	end
  end

  local cache = rawgettable(t,"_methodcache");
  if cache then
     local item = rawgettable(cache,f)
     if item then
       return item
     end
  else
     cache = {}
     rawsettable(t,"_methodcache",cache); -- make the method cache!
  end

  local p = t["_parents"];

  if (type(p) == 'table') then
     local cur_index = 1; -- start at 1
	 local cur_data;

	 repeat
	   cur_data = p[cur_index];
	   if (type(cur_data) == 'table') then
	       local result = cur_data[f];
	       if (result ~= nil) then
                       if type(result) == "function" then
                         rawsettable(cache,f,result);
                       --else 
                       --  rawsettable(cache,f,result);
                       end
		       return result;        -- we found a match
		   end
	   else
	       if (OldIndex) then
		      return OldIndex(t,f);
		   else
		      return nil;
		   end
	   end
	   cur_index = cur_index + 1; -- do next parent
	 until (cur_data == nil);

	 return nil; -- we didn't find a match
  else 
     return nil;
  end
end

----------------------------------------------------------
-- AdvProtoIndexWithCache
--
-- This inheritence tag method handles multiple inheritence via a
-- "_parent = {}" table. It caches information in the top-level table
-- to make lookups fast.
--
-- Example:
--
-- This tag method is applied to all tables, so all you have to do to
-- get a magic inheritence table is to do this:
--
-- BaseObj1 = { a_value = "a" }
-- BaseObj2 = { b_value = "b" }
-- MyClass  = { _parents = { BaseObj2, BaseObj1 } }
-- MyInstance = { _parents = { MyClass }
--
-- NOTE: Because setting a slot to the "nil" value causes it to
--       disappear, using "nil" valued slots with inheritence causes
--       some strange behavior. Namely, if you have a variable in
--       a parent class somewhere, there is no direct way to override
--       it with "nil", since setting "nil" will merely erase your
--       instance's copy of the value and cause chaining to the parent
--       again. The only way to set a nil value, would be to directly
--       insert the magic "NIL_OBJECT" into the _slotcache, so that
--       it would be seen before the lookup to the parent was
--       attempted. However, no factility to do this has been
--       provided.
--
--
---- About the "_slotcache":
----
---- The cache is automatically created and stored in a slot called the
---- "_slotcache".  Functions are pointed to directly, other items are
---- pointed to using something called a "SLOT_REF", which is basically
---- a table which contains a refernece to the object and the name of
---- the slot. This allows "references" to values to exist, so that
---- when you change a value (such as a number) in a base class, the
---- instances will see the new version of the value. I think right now
---- it is making references to tables, which is not necessary. It
---- would be slightly faster if it treated tables like functions.
----
---- There is also some magic to handle 
----
---- It could be even faster if it would actually make a copy of the 
---- value, and make a "note" in the superclass that the value was
---- cached somewhere. Then if the value was changed in the superclass,
---- the relatively expensive "invalidate" could be performed. This would
---- make changing a value in a superclass more expensive, but reading
---- the value in the instance cheaper, just as it should be.
----

function setupMultipleInheritenceForTag(a_tag) 
    -- I like to setup my tag methods within a function because
    -- then stuff like these private declarations can be
    -- referenced with upvalues and disappear. :)

    local NIL_OBJECT = { magic_nil_object = 1}
    local SLOT_REF_TAG = newtag()
    local OldIndex = gettagmethod(tag({}),"index")
    local debug_mode = nil

    AdvProtoIndexWithCache = function (t,f, instance, depth)
      if (f == '_parents') or (f == '_slotcache') then -- to avoid loop
	if (%OldIndex) then
		return %OldIndex(t,f)
	    else
		return nil;
	    end
      end


      if instance == nil then
	-- we are the instance!
	instance = t 
      end
      if depth == nil then
	depth = 0
      end

      -- get out the parent table
      local p = rawgettable(t,"_parents")

      local cache = rawgettable(instance,"_slotcache");
      if cache then
	 local item = rawgettable(cache,f)
	 if item then
	   if item == %NIL_OBJECT then
	     return nil
	   elseif tag(item) == %SLOT_REF_TAG then
	     return item.obj[f]
	   else
	     return item
	   end
	 end
      else
	 -- if we are the instance AND we had a _parents
	 -- slot, then create the slot cache!

	 if (instance == t) and (p) then
	   cache = {}
	   rawsettable(t,"_slotcache",cache); -- make the slot cache!
	 end
      end

      if (type(p) == 'table') then
	 local cur_index = 1; -- start at 1
	     local cur_data;


	     repeat
	       cur_data = p[cur_index];

	       if (%debug_mode) then
		 print("---------", cur_index, depth)
	       end
	       if (type(cur_data) == 'table') then
		   if (%debug_mode) then
		     printTables(cur_data)
		   end

		 -- local result = cur_data[f];
		   local result = rawgettable(cur_data,f);

		   if (%debug_mode and (result ~= nil)) then
		     print("value: ", result)
		   end

		   -- if we found the slot in us, then we need
		   -- to do the caching, because after we return
		   -- it's not possible to make a SLOT_REF
		   if ((result ~= nil) and (cache)) then
                     rawsettable(instance,f,result);
		   end

		   if (result == nil) then
		     result = AdvProtoIndexWithCache(cur_data,f,instance, depth + 1)
		   end

		   if (result ~= nil) then
		     if (%debug_mode and (result ~= nil)) then
		       print("value: ", result) 
		     end

		     return result;        -- we found a match
		   end
	       else
		   local result 

		   if (%OldIndex) then
		     result = %OldIndex(t,f);
		   else
		     result = nil;
		   end

			   if cache then
			     if (type(result) == "function") then
			       rawsettable(cache,f,result);
			     elseif result == nil then 
			       rawsettable(cache,f,%NIL_OBJECT)
			     else
			       local slot_ref = { obj = cur_data }
			       settag(slot_ref,%SLOT_REF_TAG);
			       rawsettable(cache,f,slot_ref);
			     end
			   end
			   return result;        -- we found a match


	       end
	       cur_index = cur_index + 1; -- do next parent
	     until (cur_data == nil);

	     if cache then
	       rawsettable(cache,f,%NIL_OBJECT)
	     end

	     return nil; -- we didn't find a match
      else 
	 return nil;
      end
    end


    settagmethod(a_tag,"index",AdvProtoIndexWithCache);  -- lua 3.1 method
end

-- NOW, actually turn-on this fancy inheritence stuff!

setupMultipleInheritenceForTag(tag({}))


----------------------------------------------------------------------


function add_parent(obj, par) 
  if (obj._parents == nil) then
      obj._parents = {}; -- create a parents table
  end

  local parents_table = obj._parents; -- get the parents table
  local cur_index = 1;
  local cur_data = parents_table[cur_index];

  while (cur_data ~= nil) do
     cur_data = parents_table[cur_index];
	 cur_index = cur_index + 1;
  end

  parents_table[cur_index] = par; -- add new parent
  
end

OldIndex = settagmethod(tag({}),"index",AdvProtoIndex);  -- lua 3.1 method


function luaStatus(message)
	print(message);
end


-- init.lua main code start...
luaStatus("[init.lua]: loading objects");



