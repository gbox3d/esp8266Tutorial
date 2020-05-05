--
-- Created by IntelliJ IDEA.
-- User: gbox3d
-- Date: 2019-03-01
-- Time: 15:25
-- To change this template use File | Settings | File Templates.
--

if not file.exists("a.lc") then
    print([[a.lc node found]])
    node.compile('a.lua')
    node.restart()
else
    dofile('a.lc')
end