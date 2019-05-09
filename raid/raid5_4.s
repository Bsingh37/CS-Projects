.data			
temp1: .long 0  						# to store current index for disk1
temp2: .long 0							# to store current index for disk2
temp3: .long 0							# to store current index for disk3
temp4: .long 0							# to store current index for disk4
temp5: .long 0							# to store current index for disk5 
longDivisor: .long 4
temp1a: .long 0  						# to store current index for disk1 to rebuild string
temp2a: .long 0							# to store current index for disk2 to rebuild string
temp3a: .long 0							# to store current index for disk3 to rebuild string
temp4a: .long 0							# to store current index for disk4 to rebuild string
temp5a: .long 0							# to store current index for disk5 to rebuild string

# Stack frame 
		.equ	srcPtr, -8							# pointer to traverse through input string
        .equ    input ,-89							# equates input to 81 characters
        .equ	counter, -93						# user's choice of disk to corrupt (1-5)
        .equ 	disk1, -109							# arrays of 16 elements
        .equ	disk2, -125
        .equ	disk3, -141
        .equ	disk4, -157
        .equ	disk5, -173
        .equ	parity, -189
        .equ	parityIndex, -193					# index for parity disk
        .equ	output, -274						# output string
        .equ    localSize,-288						# equates localSize to -288
        
        .section .rodata       						# the read-only data section 
prompt: 
        .string "Enter a sentence: " 
        .equ    promptSz,.-prompt-1 				#equates promptSz to the size of prompt
endline:
		.string "\n"
		.equ    endlineSz,.-endline-1
		
displD1: 
		.string "Disk 1: "
		.equ    displD1Sz,.-displD1-1
		
displD2:
		.string "Disk 2: "
		.equ    displD2Sz,.-displD2-1
		
displD3:
		.string "Disk 3: "
		.equ    displD3Sz,.-displD3-1
		
displD4:
		.string "Disk 4: "
		.equ    displD4Sz,.-displD4-1
		
displD5:
		.string "Disk 5: "
		.equ    displD5Sz,.-displD5-1
		
displP:
		.string "Parity: "
		.equ    displPSz,.-displP-1
		
coruptChoice:
		.string "Choose disk to corupt: "
		.equ	coruptChoiceSz, .-coruptChoice-1
		
recoverMsg:
		.string "Recovering disk...\n\n"
		.equ	recoverMsgSz, .-recoverMsg-1
		
displOutput:
		.string "Fully Restored String: "
		.equ	displOutputSz, .-displOutput-1
        .text                  
        .globl  _start 
_start: 
        pushq   %rbp           						# save caller’s frame pointer 
        movq    %rsp, %rbp     						# establish our frame pointer 
        addq    $localSize, %rsp  					# for local variable 
        xorq	%r13, %r13							# clear register for jump
        movl    $promptSz, %edx 					# prompt size 
        movl    $prompt, %esi  						# address of prompt text string 
        movl    $1, %edi  							# standard out 
        movl    $1, %eax 							# 1 for WRITE
        syscall                						# request kernel service
        
        movl    $81, %edx       					# max 80 characters and newline of input string
        leaq    input(%rbp), %rsi 					# place to store characters 
        movl    $0, %edi       						# standard in 
        movl    $0, %eax 
        syscall                						# request kernel service
        
        pushq	%rax								# save register
		leaq	input(%rbp), %rax					# copy input string adress into %rax
		movq 	%rax, srcPtr(%rbp)					# initiate pointer to the adress of the beginning of the string
		
diskD1:	
		movl	temp1, %r8d							# initiate index for disk1
		cltd
diskD1up:		
		movq 	srcPtr(%rbp), %rax					# copy pointer for dereferencing
		movb    (%rax), %al      					# one char is copied to %al
		cmpb    $0xa, %al          					# check, if the char is the end of string 
        jle      displayDisk1
        movb 	%al, disk1(%rbp,%r8,1)				# copy one char to disk1
        incq 	%r8									# increment index by 1
        incq 	srcPtr(%rbp)						# increment pointer by 1
        movl	%r8d, temp1							# save current index for disk1 in temp1 var
        movl	%r8d, %eax							# prepare registers for division
        cltd
        divl	longDivisor							# divide current index by 4
        cmpl	$0, %edx							# check if remainder is 0, 
        jle		diskD2								# if yes, 4 chars are copied, jump to disk2
        jmp 	diskD1up							# if not, proceed coping chars in the same disk			 
diskD2:				
        movl	temp2, %r8d							# load index for disk2
		cltd
diskD2up:
		movq 	srcPtr(%rbp), %rax
		movb    (%rax), %al      					# one char is copied to %al
		cmpb    $0xa, %al        					# check, if the char is the end of string 
        jle      displayDisk1						# if yes, display disks   
        movb 	%al, disk2(%rbp,%r8,1) 				# if not, proceed copying chars in the same disk
        incq 	%r8
        incq 	srcPtr(%rbp)
        movl	%r8d, temp2							# save incremented index for disk2    
        movl 	%r8d, %eax
        cltd
        divl	longDivisor
        cmpl	$0, %edx
        jle	diskD3									# if true, 4 chars are copied, jump to disk3
        jmp diskD2up   
diskD3:
        movl	temp3, %r8d	
		cltd
diskD3up:
        movq 	srcPtr(%rbp), %rax
		movb    (%rax), %al      					# one char is copied to %al
		cmpb    $0xa, %al         					# check, if the char is the end of string 
        jle      displayDisk1    
        movb 	%al, disk3(%rbp, %r8, 1) 			# if not, proceed copying chars in the same disk
        incq 	%r8
        incq 	srcPtr(%rbp)
        movl	%r8d, temp3							# save incremented index for disk3      
        movl 	%r8d, %eax
        cltd
        divl	longDivisor
        cmpl	$0, %edx
        jle		diskD4								# if true, 4 chars are copied, jump to disk4
        jmp 	diskD3up     
diskD4:
        movl	temp4, %r8d	
		cltd
diskD4up:
        movq 	srcPtr(%rbp), %rax
		movb    (%rax), %al      					# one char is copied to %al
		cmpb    $0xa, %al         					# check, if the char is the end of string 
        jle     displayDisk1    
        movb 	%al, disk4(%rbp,%r8,1) 
        incq 	%r8
        incq 	srcPtr(%rbp)
        movl	%r8d, temp4							# save incremented index for disk4   
        movl 	%r8d, %eax
        cltd
        divl	longDivisor
        cmpl	$0, %edx
        jle		diskD5								# if true, 4 chars are copied, jump to disk5
        jmp 	diskD4up
diskD5:
        movl	temp5, %r8d
		cltd
diskD5up:
        movq 	srcPtr(%rbp), %rax
		movb    (%rax), %al      					# one char is copied to %al
		cmpb    $0xa, %al          					# check, if the char is the end of string 
        jle     displayDisk1
        movl	%r8d, temp5
        movb 	%al, disk5(%rbp,%r8,1) 
        incq 	%r8
        incq 	srcPtr(%rbp)
        movl 	%r8d, temp5							# save incremented index for disk5   
        movl 	%r8d, %eax
        cltd
        divl	longDivisor
        cmpl	$0, %edx
        jle		diskD1								# if true, 4 chars are copied, jump to disk1
        jmp 	diskD5up
        
displayDisk1:		
		movq    $displD1Sz, %rdx 					# prompt size 
        movq    $displD1, %rsi  					#address of prompt text string 
        movq    $1, %rdi  							# standard out 
        movq    $1, %rax 
        syscall      
		xorq 	%rdx, %rdx
		movl    temp1, %edx 						# disk1 size equals to value in temp1
        leaq    disk1(%rbp), %rsi  					# address of disk1 
        movq    $1, %rdi  							# standard out 
        movq    $1, %rax 
        syscall      
		movq    $endlineSz, %rdx 					# endline size 
        movq    $endline, %rsi  					# address of endline string 
        movq    $1, %rdi  							# standard out  
        movq    $1, %rax 
        syscall  

displayDisk2:		
		movq    $displD2Sz, %rdx 					# prompt size 
        movq    $displD2, %rsi  					# address of prompt text string 
        movq    $1, %rdi  							# standard out 
        movq    $1, %rax 
        syscall     
		xorq 	%rdx, %rdx
		movl    temp2, %edx 						# disk2 size equals to value in temp2
        leaq    disk2(%rbp), %rsi  					# address of disk2 
        movq    $1, %rdi  							# standard out 
        movq    $1, %rax 
        syscall     
        movq    $endlineSz, %rdx 					# endline size 
        movq    $endline, %rsi  					# address of endline string 
        movq    $1, %rdi  							# standard out  
        movq    $1, %rax 
        syscall  

displayDisk3:		
		movq    $displD3Sz, %rdx 					# prompt size 
        movq    $displD3, %rsi  					# address of prompt text string 
        movq    $1, %rdi  							# standard out 
        movq    $1, %rax 
        syscall  
		xorq 	%rdx, %rdx
		movl    temp3, %edx 						# disk3 size equals to value in temp3 
        leaq    disk3(%rbp), %rsi  					# address of disk3 
        movq    $1, %rdi  							# standard out 
        movq    $1, %rax 
        syscall  
        movq    $endlineSz, %rdx 					# endline size 
        movq    $endline, %rsi  					# address of endline string 
        movq    $1, %rdi  							# standard out 
        movq    $1, %rax 
        syscall  
        
displayDisk4:		
		movq    $displD4Sz, %rdx 					# prompt size 
        movq    $displD4, %rsi  					# address of prompt text string 
        movq    $1, %rdi  							# standard out 
        movq    $1, %rax 
        syscall 
		xorq 	%rdx, %rdx
		movl    temp4, %edx 						# disk4 size equal to valu in temp4 
        leaq    disk4(%rbp), %rsi  					# address of disk4 
        movq    $1, %rdi  							# standard out 
        movq    $1, %rax 
        syscall  
        movq    $endlineSz, %rdx 					# endline size 
        movq    $endline, %rsi  					# address of endline string 
        movq    $1, %rdi  							# standard out 
        movq    $1, %rax 
        syscall 

displayDisk5:		
		movq    $displD5Sz, %rdx 					# prompt size 
        movq    $displD5, %rsi  					# address of prompt text string 
        movq    $1, %rdi  							# standard out 
        movq    $1, %rax 
        syscall 
		xorq 	%rdx, %rdx
		movl    temp5, %edx 						# disk size equals to value stored in temp5 
        leaq    disk5(%rbp), %rsi  					# address of disk5 
        movq    $1, %rdi  							# standard out 
        movq    $1, %rax 
        syscall    
        movq    $endlineSz, %rdx 					# endline size 
        movq    $endline, %rsi  					# address of endline string 
        movq    $1, %rdi  							# standard out 
        movq    $1, %rax 
        syscall  
        cmpq	$10, %r13							# check, if disks are recovered
        je		unStripePrep 						# if yes, rebuild the string
		cmp		$0, counter(%rbp)					# check, if user chose disk to corrupt
		jne		recover								# if yes, start recovering
		
parityDisk:
		movl	$0, parityIndex(%rbp)				# initiate index for parityDisk
		cltd
		xorq %r8, %r8
		xorq %r9, %r9
		movl temp1, %r9d							# copy size of disk1 into register			
parityDiskUp:
		movl parityIndex(%rbp), %r8d				# copy index into register
		xorq %rax, %rax								# clear register
		cmpl	%r9d, %r8d							# check, if array is ended
		je	displayParity							# if yes, display parity disk
		movb disk1(%rbp, %r8, 1), %al				# copy 1 element from disk1 into %al					
		xorb disk2(%rbp, %r8, 1), %al				# xor element and save reult to %al
		xorb disk3(%rbp, %r8, 1), %al				
		xorb disk4(%rbp, %r8, 1), %al
		xorb disk5(%rbp, %r8, 1), %al
		movb %al, parity(%rbp, %r8, 1)				# copy the last XORed element to parity disk
		incl parityIndex(%rbp)						# increment parity index 
		jmp parityDiskUp							# proceed loop	
displayParity:
		movq    $displPSz, %rdx 					# prompt size 
        movq    $displP, %rsi  						# address of prompt text string 
        movq    $1, %rdi  							# standard out 
        movq    $1, %rax 
        syscall 
		xor 	%rdx, %rdx
		movl 	parityIndex(%rbp), %edx				# parity disk size stored in parityIndex
		leaq    parity(%rbp), %rsi  				# address of prompt text string 
        movq    $1, %rdi  							# standard out 
        movq    $1, %rax 
        syscall   
        movq    $endlineSz, %rdx 					# endline size 
        movq    $endline, %rsi  					# address of endline string 
        movq    $1, %rdi  							# standard out 
        movq    $1, %rax 
        syscall
corupt1:        
      	movl    $coruptChoiceSz, %edx 				# prompt size 
        movl    $coruptChoice, %esi  				# address of prompt text string 
        movl    $1, %edi  							# standard out 
        movl    $1, %eax 							# 1 for WRITE
        syscall                						# request kernel service 			
      	movl    $2, %edx 							# user's choice of disk string size 
        leaq    counter(%rbp), %rsi  				# address of user's choice of disk string 
        movl    $0, %edi  							# standard out 
        movl    $0, %eax 							# 0 for READ
        syscall                						# request kernel service    
		cmpb 	$'1', counter(%rbp)					# check, if user chooses disk1 to corupt
		jne 	corupt2								# if not, jump to disk2
		movq 	$0, disk1(%rbp)						# if disk1, load 0's into first 8 bytes of disk
		movq	$0, -101(%rbp)						# load 0's into 2nd 8 bytes of disk
		jmp		displayDisk1						# jump to display disks
corupt2:
		cmpb	$'2', counter(%rbp)					# check, if user chooses disk2 to corupt
		jne 	corupt3								# if not, jump to disk3
		movq	$0, disk2(%rbp)						# if disk2, load 0's into first 8 bytes of disk
		movq	$0, -117(%rbp)						# load 0's into 2nd 8 bytes of disk
		jmp		displayDisk1
corupt3:
		cmpb	$'3', counter(%rbp)					# check, if user chooses disk3 to corupt
		jne 	corupt4								# if not, jump to disk4
		movq	$0, disk3(%rbp)						# if disk3, load 0's into first 8 bytes of disk
		movq	$0, -133(%rbp)						# load 0's into 2nd 8 bytes of disk
		jmp		displayDisk1
corupt4:
		cmpb	$'4', counter(%rbp)					# check, if user chooses disk4 to corupt
		jne 	corupt5								# if not, jump to disk5
		movq	$0, disk4(%rbp)						# if disk4, load 0's into first 8 bytes of disk
		movq	$0, -149(%rbp)						# load 0's into 2nd 8 bytes of disk
		jmp		displayDisk1
corupt5:
		movq	$0, disk5(%rbp)						# if disk5, load 0's into first 8 bytes of disk
		movq	$0, -165(%rbp)						# load 0's into 2nd 8 bytes of disk
		jmp		displayDisk1
		
recover:
		movl    $recoverMsgSz, %edx 				# prompt size 
        movl    $recoverMsg, %esi  					# address of prompt text string 
        movl    $1, %edi  							# standard out 
        movl    $1, %eax 							# 1 for WRITE
        syscall                						# request kernel service 
		movl	$0, parityIndex(%rbp)				# initiate parity index
		cltd
		xorq	%r8, %r8							# clear registers
		xorq	%r9, %r9
		movl 	temp1, %r9d							# copy disk1 size into register

recoverUp:
		movl 	parityIndex(%rbp), %r8d				# copy parity index into register
		xorq 	%rax, %rax							# clear register
		cmpl	%r9d, %r8d							# check, if disk1 ended
		je		restore								# if yes, restore disks
		movb 	parity(%rbp, %r8, 1), %al			# copy 1 element from parity into %al
		xorb 	disk1(%rbp, %r8, 1), %al			# xor elements and save result in %al			
		xorb 	disk2(%rbp, %r8, 1), %al				
		xorb 	disk3(%rbp, %r8, 1), %al				
		xorb 	disk4(%rbp, %r8, 1), %al
		xorb 	disk5(%rbp, %r8, 1), %al
		movb 	%al, parity(%rbp, %r8, 1)			# copy the last XORed element to parity disk
		incl 	parityIndex(%rbp)					# increment index
		jmp 	recoverUp							# proceed loop
		
restore:
		movq	$0, %r8								# initiate index for parity disk
		xorq 	%rax, %rax							# clear register
		movq	$10, %r13							# mark that disks are recovered
		xorq 	%r10, %r10							
		movl	parityIndex(%rbp), %r10d			# copy parity disk size into register
restore1:
		cmpb	$'1', counter(%rbp)					# check, if disk1 was corupted
		jne		restore2							# if not, jump to restore disk2
		cmpl	%r10d, %r8d							# if yes, check if parity disk ended
		ja	 	displayDisk1						# if yes, diskplay restored disks
		movb	parity(%rbp, %r8, 1), %al			# if not, copy one byte of parity disk to %al
		movb 	%al, disk1(%rbp, %r8, 1)			# copy %al to previously corrupted disk
		incq	%r8									# increment index
		jmp 	restore1							# loop back to beginning of restore1
restore2:
		cmpb	$'2', counter(%rbp)
		jne		restore3
		cmpl	%r10d, %r8d							# check, if parity disk ended
		ja	 	displayDisk1
		movb	parity(%rbp, %r8, 1), %al
		movb 	%al, disk2(%rbp, %r8, 1)
		incq	%r8
		jmp 	restore2
restore3:
		cmpb	$'3', counter(%rbp)
		jne		restore4
		cmpl	%r10d, %r8d							# check, if parity disk ended
		ja	 	displayDisk1
		movb	parity(%rbp, %r8, 1), %al
		movb 	%al, disk3(%rbp, %r8, 1)
		incq	%r8
		jne 	restore3
restore4:
		cmpb	$'4', counter(%rbp)
		jne		restore5
		cmpl	%r10d, %r8d							# check, if parity disk ended
		ja	 	displayDisk1
		movb	parity(%rbp, %r8, 1), %al
		movb 	%al, disk4(%rbp, %r8, 1)
		incq	%r8
		jne 	restore4
restore5:
		cmpl	%r10d, %r8d							# check, if parity disk ended
		ja	 	displayDisk1
		movb	parity(%rbp, %r8, 1), %al
		movb 	%al, disk5(%rbp, %r8, 1)
		incq	%r8
		jne 	restore5

unStripePrep:
		xorq %rax, %rax
		xorq %r8, %r8								# Clear all indicies
		xorq %r10, %r10
		xorq %r9, %r9
unStripe1:
		movl	temp1, %r9d							# copy original disk1 size into register
		movl	temp1a, %r10d						# copy current disk1 size into register
		cmpl	%r9d, %r10d							# check, if restored disk copied into string
		ja		displayOutput						# if yes, display string
		movb 	disk1(%rbp,%r10,1), %al				# copy one char from disk to al
		movb	%al, output(%rbp, %r8, 1)			# copy char from al to string
        incq 	%r8									# incement index by 1
        incq	%r10								# increment index by 1
        movl	%r10d, temp1a						# save current size of disk1
        movl	%r8d, %eax							# prepare registers for division
        cltd
        divl	longDivisor							# divide current index by 4
        cmpl	$0, %edx							# check if remainder is 0, 
        jle		unStripe2							# if yes, jump to unstripe disk 2
        jmp 	unStripe1							#i f not, proceed coping chars in the same disk	
unStripe2:
		movl	temp2, %r9d
		movl	temp2a, %r10d
		cmpl	%r9d, %r10d							# check, if restored disk copied into string					
		ja	displayOutput       
		movb 	disk2(%rbp,%r10,1), %al				# copy one char from disk to al
		movb	%al, output(%rbp, %r8, 1)			# copy char into output string
        incq 	%r10								# increment index by 1
        movl	%r10d, temp2a						# save current size of disk2
        inc		%r8									# increment index by 1
        movl	%r8d, %eax							# prepare registers for division
        cltd
        divl	longDivisor							# divide current index by 4
        cmpl	$0, %edx							# check if remainder is 0, 
        jle		unStripe3							# if yes, jump to unstripe 3
        jmp 	unStripe2							# if not, proceed coping chars in the same disk

unStripe3:
		movl	temp3, %r9d
		movl	temp3a, %r10d
		cmpl	%r9d, %r10d							# check, if restored disk copied into string
		ja		displayOutput
		movb 	disk3(%rbp,%r10,1), %al				# copy one char from disk to al
		movb	%al, output(%rbp, %r8, 1)			# copy char into output string
        incq 	%r10								# increment index by 1
        movl	%r10d, temp3a						# save current size of disk 3
        incq	%r8									# increment index by 1
        movl	%r8d, %eax							# prepare registers for division
        cltd
        divl	longDivisor							# divide current index by 4
        cmpl	$0, %edx							# check if remainder is 0, 
        jle		unStripe4							# if yes, jump to unstripe disk 4
        jmp 	unStripe3							# if not, proceed coping chars in the same disk
unStripe4:
		movl	temp4, %r9d
		movl	temp4a, %r10d
		cmpl	%r9d, %r10d							# check, if restored disk copied into string
		ja		displayOutput
		movb 	disk4(%rbp,%r10,1), %al				# copy one char from disk to al
		movb	%al, output(%rbp, %r8, 1)			# copy into output string
        incq 	%r10								# increment index
        movl	%r10d, temp4a						# save current size of disk4
        incq	%r8									# increment index by 1
        movl	%r8d, %eax							# prepare registers for division
        cltd
        divl	longDivisor							# divide current index by 4
        cmpl	$0, %edx							# check if remainder is 0, 
        jle		unStripe5							# if yes, jump to unstripe disk 5
        jmp 	unStripe4							# if not, proceed coping chars in the same disk
unStripe5:
		movl	temp5, %r9d
		movl	temp5a, %r10d
		cmpl	%r9d, %r10d							# check, if restored disk copied into string
		ja		displayOutput	
		movb 	disk5(%rbp,%r10,1), %al				# copy one char from disk to al
		movb	%al, output(%rbp, %r8, 1)			# copy char into output string
        incq 	%r10								# index++
        movl	%r10d, temp5a
        incq	%r8									# increment index by 1
        movl	%r8d, %eax							# prepare registers for division
        cltd
        divl	longDivisor							# divide current index by 4
        cmpl	$0, %edx							# check if remainder is 0, 
        jle		unStripe1							# if yes, jump to disk1
        jmp 	unStripe5							#if not, proceed coping chars in the same disk
        	
displayOutput: 
		movq    $displOutputSz, %rdx 				# prompt size 
        movq    $displOutput, %rsi  				#address of prompt text string 
        movq    $1, %rdi  							# standard out 
        movq    $1, %rax 
        syscall  
		xorq 	%rdx, %rdx
		popq	%rdx 								# string size 
        leaq    output(%rbp), %rsi  				# address of output string 
        movq    $1, %rdi  							# standard out 
        movq    $1, %rax 
        syscall  
        movq    $endlineSz, %rdx 					# endline size 
        movq    $endline, %rsi  					# address of endline string 
        movq    $1, %rdi  							# standard out 
        movq    $1, %rax 
        syscall  
end:        
		movq    %rbp, %rsp     						# delete local variables 
        popq    %rbp           						# restore caller’s frame pointer 
        movl    $60, %eax    						# exit from this process 
        syscall
         	
