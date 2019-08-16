local M = {}

M.msg = "my name is foo"

local private_val = "i m privercy important"

local function private_func()
    print(private_val)
end

function M.hello(  )
    print("hello module")
    private_func()
end

return  M