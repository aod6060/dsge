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

export(state, "test_int_2", LWType.LWT_INTEGER)
test_int_2 = 100

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
    print("test_int_2: "..test_int_2)

    print()

end


function test_app_interface()
    -- Add other functions to this in a second.

    width = App.getWidth()
    height = App.getHeight()
    aspect = App.getAspect()

    print(width .. ", " .. height .. ", " .. aspect)

end

function test_app_exit()
    App.exit()
end

i = 0

-- This function will be called in the update function
function update(delta)
end