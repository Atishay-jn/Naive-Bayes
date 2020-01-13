# Pass 1 of Assembler

# Importing CSV library for reading and writing from files
import csv

def opcode():
	# The function is responsible for creating OP-Code Table for the assembler along with
	# mentioning the number of parameters each instruction can take
	Memory_ref_instruction = True
	Non_Memory_ref_instruction = False
	opcode_table = {
		"CLA" : ("0000", Non_Memory_ref_instruction, 0),
		"LAC" : ("0001", Memory_ref_instruction, 1),
		"SAC" : ("0010", Memory_ref_instruction, 1),
		"ADD" : ("0011", Memory_ref_instruction, 1),
		"SUB" : ("0100", Memory_ref_instruction, 1),
		"BRZ" : ("0101", Non_Memory_ref_instruction, 1),
		"BRN" : ("0110", Non_Memory_ref_instruction, 1),
		"BRP" : ("0111", Non_Memory_ref_instruction, 1),
		"INP" : ("1000", Memory_ref_instruction, 1),
		"DSP" : ("1001", Memory_ref_instruction, 1),
		"MUL" : ("1010", Memory_ref_instruction, 1),
		"DIV" : ("1011", Memory_ref_instruction, 1),
		"STP" : ("1100", Non_Memory_ref_instruction, 0)
	}
	return opcode_table

def ret_binary(n):
	#function to return binary equivalent in 12 bits
	x=str(bin(int(n)))[(str(bin(int(n))).find('b')+1):]
	return '0'*(12-len(x))+x

def takeInput():
	#Used to take input from the files
	line = []
	file = open("input.txt","r")
	f1 = file.readlines()
	for i in range(0,len(f1)):
		if(i!=len(f1)-1):
			f1[i] = f1[i][0:-1]
		a = f1[i].split()
		line.append(a)
	return line
		
program = takeInput()
opcode_table = opcode()
symbol_table = {}

flag = True
i = -1
while(i<len(program)-1):
	#Traversing the code line by line
	i+=1
	if(flag):
		if(program[i][0][-1] == ":"):
			if len(program[i][0])==1:
				print("ERROR: Invalid label name is being used in line",i)
			if(symbol_table.get(program[i][0][:-1],-2)==-2):
				symbol_table[program[i][0][:-1]] = (i,'-')
				program[i] = program[i][1:]
			else:
				print("ERROR: Unable to assign the given label multiple addresses:", program[i][0][:-1])
				program[i] = program[i][1:]
		if(flag and program[i][0] == "STP"):
			flag = False
		if(not(program[i][0] in opcode_table)):
			print("ERROR: Invalid program instruction:",program[i][0],"in line",i)
			program = program[:i] + program[i+1:]
			i -= 1
			continue
		temp = opcode_table[program[i][0]]
		comment = -1
		for j in range(len(program[i])):
			if(len(program[i][j])>=2 and program[i][j][0]=="/" and program[i][j][1]=="/"):
				comment = j
				break
		if(comment != -1):
			program[i] = program[i][:comment]
		if(len(program[i])>1+temp[2]):
			print("ERROR: Too many parameters in line",i,":",program[i])
			error_var=1
		if temp[2]>0:
			try:
				if symbol_table.get(program[i][1],-1) == -1:
					symbol_table[program[i][1]] = -2
			except IndexError:
				print("ERROR: Not enough parameters have been passed for the given instruction in line",i,":",program[i][0])
	else:
		if(not(flag) and program[i][0] == "STP"):
			print("ERROR: The code has multiple stops.")
			error_var=1
		if(program[i][0][-1] == ":"):
			if symbol_table.get(program[i][0][:-1],-2)==-2:
				try:
					symbol_table[program[i][0][:-1]] = (i,program[i][1])
					program[i] = program[i][1:]
				except IndexError:
					print("ERROR: Declaration not done properly in line",i,":",''.join(program[i]))
					program = program[:i] + program[i+1:]
					i -= 1
			else:
				print("ERROR: Variable has been declared multiple times:",program[i][0][:-1])
				program = program[:i] + program[i+1:]
				i -= 1
		else:
			print("Invalid instruction/declaration",''.join(program[i]),"in line",i)
			program = program[:i] + program[i+1:]
			i -= 1
if(flag):
	print("ERROR: Stop missing in the code")

for i in range(len(program)):
	if len(program[i])==1:
		continue

with open('opcode_table.csv', 'w') as f:
	# Writing op_code table to csv file
	f.write("%s,%s,%s,%s\n"%("assembly_opcode","machine_opcode","memory_reference_instruction(T/F)","Number of Operands"))
	for key in opcode_table.keys():
		f.write("%s,%s,%s,%s\n"%(key,opcode_table[key][0],opcode_table[key][1],opcode_table[key][2]))

with open('symbol_table.csv', 'w') as f:
	# Writing symbol table to csv file
	f.write("%s,%s,%s\n"%("name","address","vallue"))
	for key in symbol_table.keys():
		try:
			f.write("%s,%s,%s\n"%(key,symbol_table[key][0],symbol_table[key][1]))
		except:
			f.write("%s,%s,%s\n"%(key,symbol_table[key],"-"))

outF = open("pass1_out.txt", "w")

for line in program:
  outF.write(" ".join(line))
  outF.write("\n")
outF.close()
