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
 addi $sp, $sp, -56
 lw $t0, 8($fp)
 sw $t0, -4($fp)
 li $t0, 1
 sw $t0, -8($fp)
 lw $t1, -8($fp)
 sw $t1, -12($fp)
 li $t0, 1
 sw $t0, -16($fp)
 lw $t1, -16($fp)
 sw $t1, -20($fp)
label0:
 lw $t1, -20($fp)
 sw $t1, -24($fp)
 lw $t1, -4($fp)
 sw $t1, -28($fp)
 lw $t1, -24($fp)
 lw $t2, -28($fp)
 ble $t1, $t2, label1
 j label2
label1:
 lw $t1, -12($fp)
 sw $t1, -32($fp)
 lw $t1, -20($fp)
 sw $t1, -36($fp)
 lw $t1, -32($fp)
 lw $t2, -36($fp)
 mul $t0, $t1, $t2
 sw $t0, -40($fp)
 lw $t1, -40($fp)
 sw $t1, -12($fp)
 lw $t1, -20($fp)
 sw $t1, -44($fp)
 li $t0, 1
 sw $t0, -48($fp)
 lw $t1, -44($fp)
 lw $t2, -48($fp)
 add $t0, $t1, $t2
 sw $t0, -52($fp)
 lw $t1, -52($fp)
 sw $t1, -20($fp)
 j label0
label2:
 lw $t1, -12($fp)
 sw $t1, -56($fp)
 lw $t1, -56($fp)
 move $v0, $t1
 move $sp, $fp
 lw $fp, 4($sp)
 lw $ra, 0($sp)
 addi $sp, $sp, 8
 jr $ra
main:
 addi $sp, $sp, -8
 sw $ra, 0($sp)
 sw $fp, 4($sp)
 move $fp, $sp
 addi $sp, $sp, -120
 li $t0, 0
 sw $t0, -24($fp)
 lw $t1, -24($fp)
 sw $t1, -28($fp)
 li $t0, 5
 sw $t0, -32($fp)
 lw $t1, -32($fp)
 sw $t1, -36($fp)
label3:
 lw $t1, -28($fp)
 sw $t1, -40($fp)
 lw $t1, -36($fp)
 sw $t1, -44($fp)
 lw $t1, -40($fp)
 lw $t2, -44($fp)
 blt $t1, $t2, label4
 j label5
label4:
 lw $t1, -28($fp)
 sw $t1, -48($fp)
 li $t1, -4
 move $t0, $t1
 sw $t0, -52($fp)
 lw $t1, -4($fp)
 lw $t0, 0($t1)
 sw $t0, -52($fp)
 lw $t1, -4($fp)
 lw $t0, -52($fp)
 sw $t1, 0($t0)
 lw $t1, -4($fp)
 lw $t0, -52($fp)
 lw $t2, 0($t1)
 sw $t2, 0($t0)
 lw $t1, -4($fp)
 sw $t1, -52($fp)
 lw $t1, -48($fp)
 li $t2, 4
 mul $t0, $t1, $t2
 sw $t0, -56($fp)
 lw $t1, -52($fp)
 lw $t2, -56($fp)
 add $t0, $t1, $t2
 sw $t0, -60($fp)
 lw $t1, -60($fp)
 sw $t1, -64($fp)
 lw $t1, -28($fp)
 sw $t1, -68($fp)
 li $t0, 2
 sw $t0, -72($fp)
 lw $t1, -68($fp)
 lw $t2, -72($fp)
 add $t0, $t1, $t2
 sw $t0, -76($fp)
 lw $t1, -76($fp)
 lw $t0, -64($fp)
 sw $t1, 0($t0)
 lw $t1, -76($fp)
 lw $t0, -64($fp)
 lw $t2, 0($t1)
 sw $t2, 0($t0)
 lw $t1, -76($fp)
 sw $t1, -64($fp)
 lw $t1, -28($fp)
 sw $t1, -80($fp)
 li $t1, -4
 move $t0, $t1
 sw $t0, -84($fp)
 lw $t1, -4($fp)
 lw $t0, 0($t1)
 sw $t0, -84($fp)
 lw $t1, -4($fp)
 lw $t0, -84($fp)
 sw $t1, 0($t0)
 lw $t1, -4($fp)
 lw $t0, -84($fp)
 lw $t2, 0($t1)
 sw $t2, 0($t0)
 lw $t1, -4($fp)
 sw $t1, -84($fp)
 lw $t1, -80($fp)
 li $t2, 4
 mul $t0, $t1, $t2
 sw $t0, -88($fp)
 lw $t1, -84($fp)
 lw $t2, -88($fp)
 add $t0, $t1, $t2
 sw $t0, -92($fp)
 lw $t1, -92($fp)
 lw $t0, 0($t1)
 sw $t0, -96($fp)
 lw $t1, -92($fp)
 lw $t0, -96($fp)
 sw $t1, 0($t0)
 lw $t1, -92($fp)
 lw $t0, -96($fp)
 lw $t2, 0($t1)
 sw $t2, 0($t0)
 lw $t1, -92($fp)
 sw $t1, -96($fp)
 addi $sp, $sp, -4
 lw $t1, -96($fp)
 sw $t1, 0($sp)
 jal func2
 move $t1, $v0
 sw $t1, -100($fp)
 lw $t1, -100($fp)
 sw $t1, -104($fp)
 lw $t1, -104($fp)
 move $a0, $t1
 jal write
 lw $t1, -28($fp)
 sw $t1, -108($fp)
 li $t0, 1
 sw $t0, -112($fp)
 lw $t1, -108($fp)
 lw $t2, -112($fp)
 add $t0, $t1, $t2
 sw $t0, -116($fp)
 lw $t1, -116($fp)
 sw $t1, -28($fp)
 j label3
label5:
 li $t0, 0
 sw $t0, -120($fp)
 lw $t1, -120($fp)
 move $v0, $t1
 move $sp, $fp
 lw $fp, 4($sp)
 lw $ra, 0($sp)
 addi $sp, $sp, 8
 jr $ra
