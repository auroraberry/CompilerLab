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

main:
 addi $sp, $sp, -8
 sw $ra, 0($sp)
 sw $fp, 4($sp)
 move $fp, $sp
 addi $sp, $sp, -84
 li $t0, 0
 sw $t0, -4($fp)
 lw $t1, -4($fp)
 sw $t1, -8($fp)
 li $t0, 1
 sw $t0, -12($fp)
 lw $t1, -12($fp)
 sw $t1, -16($fp)
 li $t0, 0
 sw $t0, -20($fp)
 lw $t1, -20($fp)
 sw $t1, -24($fp)
 jal read
 move $t1, $v0
 sw $t1, -28($fp)
 lw $t1, -28($fp)
 sw $t1, -32($fp)
label0:
 lw $t1, -24($fp)
 sw $t1, -36($fp)
 lw $t1, -32($fp)
 sw $t1, -40($fp)
 lw $t1, -36($fp)
 lw $t2, -40($fp)
 blt $t1, $t2, label1
 j label2
label1:
 lw $t1, -8($fp)
 sw $t1, -44($fp)
 lw $t1, -16($fp)
 sw $t1, -48($fp)
 lw $t1, -44($fp)
 lw $t2, -48($fp)
 add $t0, $t1, $t2
 sw $t0, -52($fp)
 lw $t1, -52($fp)
 sw $t1, -56($fp)
 lw $t1, -16($fp)
 sw $t1, -60($fp)
 lw $t1, -60($fp)
 move $a0, $t1
 jal write
 lw $t1, -16($fp)
 sw $t1, -64($fp)
 lw $t1, -64($fp)
 sw $t1, -8($fp)
 lw $t1, -56($fp)
 sw $t1, -68($fp)
 lw $t1, -68($fp)
 sw $t1, -16($fp)
 lw $t1, -24($fp)
 sw $t1, -72($fp)
 li $t0, 1
 sw $t0, -76($fp)
 lw $t1, -72($fp)
 lw $t2, -76($fp)
 add $t0, $t1, $t2
 sw $t0, -80($fp)
 lw $t1, -80($fp)
 sw $t1, -24($fp)
 j label0
label2:
 li $t0, 0
 sw $t0, -84($fp)
 lw $t1, -84($fp)
 move $v0, $t1
 move $sp, $fp
 lw $fp, 4($sp)
 lw $ra, 0($sp)
 addi $sp, $sp, 8
 jr $ra
