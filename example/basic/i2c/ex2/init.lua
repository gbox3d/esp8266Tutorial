
id  = 0
sda = 1
scl = 2

-- initialize i2c, set pin1 as sda, set pin2 as scl
i2c.setup(0, sda, scl, i2c.SLOW)

function sendData(addr,data)
    i2c.start(id)
    i2c.address(id, addr, i2c.TRANSMITTER)
    count = i2c.write(id, data)
    print(count, " bytes written")
    i2c.stop(id)
end

function readData(addr,bytenum)
    i2c.start(id)
    i2c.address(id, addr, i2c.RECEIVER)
    c = i2c.read(id, bytenum)
    i2c.stop(id)

    --http://lua-users.org/wiki/StringLibraryTutorial
    -- c:gsub(".", function(code) -- 한바이트씩 처리하기
    --     print(code:byte() .. '/' .. code)
    -- end)

    return c
end

print("i2c sample")

function readUnpackData(  )
    s = readData(27,16); -- 2 * 8, 아두이노에서 int형은 2바이트임 

    --아두이노에서 넘어오는 int dat[8] 읽기
    print(struct.unpack("<i2i2i2i2i2i2i2i2",s))
    r = {struct.unpack("<i2i2i2i2i2i2i2i2",s)}

    print(r[1])
    print(r[2])
    print(r[3])
    print(r[8])

end

function sendPackData()
    --[[
        아두이노에 c 구조체 형식 데이터 보내기 

struct _S_Packet {
  byte m_nSkima;
  int m_nNum;];
};
    ]]
    _s = struct.pack("Bi2",65,8266 )
    sendData(27,_s)
end
