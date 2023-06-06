# import the Template class from the string module
from string import Template

# open the file 'got.log' in read mode and assign it to the variable 'f'
with open('got.log') as f:
    # read 『all lines』 in the file and assign them to the variable 'line'
    line = f.readlines()

# loop 1477 times (range from 0 to 1476)
for i in range(1477):
    hit = 0  # initialize the variable 'hit' to 0
    # loop through each line in the list 'line'
    for j in line:
        # if the string 'code_${i} ' with the local variables substituted into the Template object
        # is equal to the first len('code_${i} ') characters in the line 'j'
        if (Template('code_${i} ').substitute(locals()) == j[0:len(Template('code_${i} ').substitute(locals()))]):
            # print the hexadecimal value of characters 13 to 17 in the line 'j' (exclusive)
            print(int(j[13:18], 16), end=', ')
            # set the variable 'hit' to 1
            hit = 1
    # if no lines match the string 'code_${i} ' with the local variables substituted into the Template object
    if (hit == 0):
        # print 0 and a comma
        print("0", end=", ")
