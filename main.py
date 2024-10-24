#permite ver como deberiamos de separar los args, cmd y demás
#command -> python3 main.py echo "'$USER'  A  " 

import sys

def main():
     print(sys.argv)

if __name__ == "__main__":
    main()