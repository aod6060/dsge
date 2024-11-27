-- test.lua
export.setInteger(state, "test_int", 1)
export.setNumber(state, "test_num", 3.16)
export.setBool(state, "test_bool", true)

test_int = export.getInteger(state, "test_int")
test_num = export.getNumber(state, "test_num")
test_bool = export.getBool(state, "test_bool")


print(test_int)
print(test_num)
print(test_bool)


function callme()
    print("Hello, World")
end