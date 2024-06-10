.data
_prompt: .asciiz "Enter an integer:"
_ret: .asciiz "\n"
.globl main
.text
read:
 li $v0, 4
 la $a0, _prompt
 syscall
 li $v0, 5
 syscall
 jr $ra

write:
 li $v0, 1
 syscall
 li $v0, 4
 la $a0, _ret
 syscall
 move $v0, $0
 jr $ra

func2:
 addi $sp, $sp, -8
 sw $ra, 0($sp)
 sw $fp, 4($sp)
 move $fp, $sp
 addi $sp, $sp, -44
 lw $t0, 8($fp)
 sw $t0, -4($fp)
 lw $t1, -4($fp)
 sw $t1, -8($fp)
 li $t0, 1
 sw $t0, -12($fp)
 lw $t1, -8($fp)
 lw $t2, -12($fp)
 beq $t1, $t2, label0
 j label1
label0:
 lw $t1, -4($fp)
 sw $t1, -16($fp)
 lw $t1, -16($fp)
 move $v0, $t1
 move $sp, $fp
 lw $fp, 4($sp)
 lw $ra, 0($sp)
 addi $sp, $sp, 8
 jr $ra
 j label2
label1:
 lw $t1, -4($fp)
 sw $t1, -20($fp)
 lw $t1, -4($fp)
 sw $t1, -24($fp)
 li $t0, 1
 sw $t0, -28($fp)
 lw $t1, -24($fp)
 lw $t2, -28($fp)
 sub $t0, $t1, $t2
 sw $t0, -32($fp)
 addi $sp, $sp, -4
 lw $t1, -32($fp)
 sw $t1, 0($sp)
 jal func2
 move $t1, $v0
 sw $t1, -36($fp)
 lw $t1, -36($fp)
 sw $t1, -40($fp)
 lw $t1, -20($fp)
 lw $t2, -40($fp)
 mul $t0, $t1, $t2
 sw $t0, -44($fp)
 lw $t1, -44($fp)
 move $v0, $t1
 move $sp, $fp
 lw $fp, 4($sp)
 lw $ra, 0($sp)
 addi $sp, $sp, 8
 jr $ra
label2:
main:
 addi $sp, $sp, -8
 sw $ra, 0($sp)
 sw $fp, 4($sp)
 move $fp, $sp
 addi $sp, $sp, -44
 jal read
 move $t1, $v0
 sw $t1, -4($fp)
 lw $t1, -4($fp)
 sw $t1, -8($fp)
 lw $t1, -8($fp)
 sw $t1, -12($fp)
 li $t0, 1
 sw $t0, -16($fp)
 lw $t1, -12($fp)
 lw $t2, -16($fp)
 bgt $t1, $t2, label3
 j label4
label3:
 lw $t1, -8($fp)
 sw $t1, -20($fp)
 addi $sp, $sp, -4
 lw $t1, -20($fp)
 sw $t1, 0($sp)
 jal func2
 move $t1, $v0
 sw $t1, -24($fp)
 lw $t1, -24($fp)
 sw $t1, -28($fp)
 lw $t1, -28($fp)
 sw $t1, -32($fp)
 j label5
label4:
 li $t0, 1
 sw $t0, -36($fp)
 lw $t1, -36($fp)
 sw $t1, -32($fp)
label5:
 lw $t1, -32($fp)
 sw $t1, -40($fp)
 lw $t1, -40($fp)
 move $a0, $t1
 jal write
 li $t0, 0
 sw $t0, -44($fp)
 lw $t1, -44($fp)
 move $v0, $t1
 move $sp, $fp
 lw $fp, 4($sp)
 lw $ra, 0($sp)
 addi $sp, $sp, 8
 jr $ra
