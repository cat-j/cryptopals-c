from argparse import ArgumentParser

# def writeBytes(srcName, dstName, writeSize=False):
#     if writeSize:
#         print("Writing size")

#     dst = open(dstName, 'wb')
#     linesRead = 0

#     if writeSize:
#         dst.write(b"\0")

#     with open(srcName, 'r+') as src:
#         # hexString = src.read()
#         # dst.write(bytearray.fromhex(hexString))
#         linesRead += 1
#         print(linesRead)
        
#     if writeSize:
#         dst.seek(0)
#         dst.write(bytes([linesRead]))

#     dst.close()
#     return

def writeBytes(srcName, dstName, writeSize=False):
    lines = open(srcName, 'r').read().splitlines()
    dst = open(dstName, 'wb')

    if writeSize:
        dst.write(bytes(str(len(lines)), 'utf-8'))
        dst.write(b'\n')
        dst.write(bytes(str(len(lines[0]) // 2), 'utf-8'))
        dst.write(b'\n')

    for l in lines:
        dst.write(bytearray.fromhex(l))
    
    dst.close()

    return

def getArgs():
    parser = ArgumentParser()
    parser.add_argument("src", help="Source file: name of file containing ASCII representation of hex string")
    parser.add_argument("dst", help="Destination file: name of file to write the results to")
    parser.add_argument("--writesize",
                        default=False,
                        help="Whether to write the number of lines read at the beginning of the file")
    args = parser.parse_args()
    return(args.src, args.dst, args.writesize)

# Generate raw byte data for challenges
def main():
    (srcName, dstName, writeSize) = getArgs()
    writeBytes(srcName, dstName, writeSize)
    return

main()