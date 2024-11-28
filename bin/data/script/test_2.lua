--[[
    This is actually a better way to handle experts
    which will make lua code to look a lot better.

    I didn't relize I could do this with lua
    
    export(variable_name, type)
]]

export(state, "test_int", LWType.LWT_INTEGER)
test_int = 1

export(state, "test_num", LWType.LWT_NUMBER)
test_num = 3.16

export(state, "test_bool", LWType.LWT_BOOL)
test_bool = true

function callme()
    print("Hello, World")

    print("test_int: "..test_int)
    print("test_num: "..test_num)
    --[[
        For values that isn't a number or string 
        use tostring function to get the value
        https://devforum.roblox.com/t/attempt-to-concatenate-string-with-boolean/843822

        Thank you roblox forum. :/
    ]]
    print("test_bool: "..tostring(test_bool))

    print()

end