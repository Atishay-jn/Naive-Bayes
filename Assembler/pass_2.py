
#checking if pass1 returned error
if False==False:
    #PASS TWO

	#function to read off the output of the pass one
	def takeInput():
	    line = []
	    file = open("pass1_out.txt","r")
	    f1 = file.readlines()
	    for i in range(0,len(f1)):
	        f1[i] = f1[i][0:-1]
	        a = f1[i].split(" ")
	        line.append(a)
	    return line

	#function to read off the opcode table convert to usable dictionary
	def opcode():
	    line = {}
	    file = open("opcode_table.csv","r")
	    f1 = file.readlines()
	    for i in range(1,len(f1)):
	        f1[i] = f1[i][0:-1]
	        a = f1[i].split(",")
	        line[a[0]]=(a[1],a[2],a[3])
	    return line

	#function to read off the symbol table and convert to usable dictionary
	def symbol():
	    line = {}
	    file = open("symbol_table.csv","r")
	    f1 = file.readlines()
	    for i in range(1,len(f1)):
	        f1[i] = f1[i][0:-1]
	        a = f1[i].split(",")
	        line[a[0]]=(a[1])
	    return line

	#function to return binary equivalent in 12 bits
	def ret_binary(n,k):
	    x=str(bin(int(n)))[(str(bin(int(n))).find('b')+1):]
	    return '0'*(k-len(x))+x
	        
	#instialisation
	program=takeInput()
	symbol_table=symbol()
	# print(symbol_table)
	opcode_table=opcode()
	input_present=False
	machine_code=[]
	location_counter=0

	if len(program)>256:
		print("ERROR: Memory overflow! Code length exceeds 256 instructions")

	for i in program:
	    # checking if instruction has 0 operands or 1 operand
	    if len(i)==1:
	        instruction_list=[]
	        #fetching binary instruction value from the opcode table
	        if i[0] in opcode_table:
	            instruction_list.append(opcode_table[i[0]][0])
	            machine_code.append(instruction_list)
	            instruction_list.append('00000000')
	        else :
	            instruction_list.append(ret_binary(i[0],12))
	            machine_code.append(instruction_list)

	    elif len(i)==2:
	        instruction_list=[]
	        if i[0] in opcode_table:
	            instruction_list.append(opcode_table[i[0]][0])
	            #checking if the operand used was a variable or direct integer value
	            if int(symbol_table[i[1]])>0:
	                #converting the offset in the symbol table to binary values and storing them in the machine code object if the operand was a variable
	                instruction_list.append(ret_binary(symbol_table[i[1]],8))
					
	            else:
	            	print("ERROR: Variables not declared in scope but has been used in line",i,":",i[1])
	        else:
	            instruction_list.append(ret_binary(i[1],8))
	        machine_code.append(instruction_list)

	#writes the value of the machine code to the txt
	outF = open("Machine.txt", "w")

	for line in machine_code:
	    outF.write(" ".join(line))
	    outF.write("\n")
	outF.close()
	loc=0
	with open('memory_map.csv', 'w') as f:
		f.write("%s,%s\n"%("address","code"))
		loc=0
		for line in machine_code:
			f.write("%s,%s\n"%(ret_binary(loc,8)," ".join(line)))
			loc+=1
	






