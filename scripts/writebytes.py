from argparse import ArgumentParser

def writeBytes(srcName, dstName):
    dst = open(dstName, 'wb')
    with open(srcName, 'r+') as src:
        hexString = src.read()
        dst.write(bytearray.fromhex(hexString))
    dst.close()
    return

def getArgs():
    parser = ArgumentParser()
    parser.add_argument("src", help="Source file: name of file containing ASCII representation of hex string")
    parser.add_argument("dst", help="Destination file: name of file to write the results to")
    args = parser.parse_args()
    return(args.src, args.dst)

# Generate raw byte data for challenges
def main():
    (srcName, dstName) = getArgs()
    writeBytes(srcName, dstName)
    return

main()