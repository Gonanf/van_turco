file = open("nabidad(1).rgba","rb")

result = "{"
cant = 0

while (byte := file.read(8)):
    binary = ""
    if byte[0] > (255/2): binary += "1"
    if byte[0] < (255/2): binary += "0"
    if byte[1] > (255/2): binary += "1"
    if byte[1] < (255/2): binary += "0"
    if byte[2] > (255/2): binary += "1"
    if byte[2] < (255/2): binary += "0"
    if byte[3] > (255/2): binary += "1"
    if byte[3] < (255/2): binary += "0"

    if byte[4] > (255/2): binary += "1"
    if byte[4] < (255/2): binary += "0"
    if byte[5] > (255/2): binary += "1"
    if byte[5] < (255/2): binary += "0"
    if byte[6] > (255/2): binary += "1"
    if byte[6] < (255/2): binary += "0"
    if byte[7] > (255/2): binary += "1"
    if byte[7] < (255/2): binary += "0"
    result += hex(int(binary,2))
    result += ","
    cant += 1
result += "};"

out = open("out.txt","x")

out.write(result)
print(cant)
