# Example:
# $ Height: 5
#     #
#    ##
#   ###
#  ####
# #####

while True:
    try:
        n = int(input("Height:"))
    except ValueError:
        continue
    if n in range(1, 9):
        break

count = 0
while(count < n):
    count = count + 1
    m = n - count
    print(" " * m + "#" * count)
