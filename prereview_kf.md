# Note

## How to review
```bash
$ valgrind --leak-check=full ./so_long ~
```

## argc = 1
```bash
 % valgrind --leak-check=full ./so_long
==549555== Memcheck, a memory error detector
==549555== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==549555== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==549555== Command: ./so_long
==549555==
==549555== Warning: client switching stacks?  SP change: 0x1ffefffd30 --> 0x1ffe85eac0
==549555==          to suppress, use: --max-stackframe=8000112 or greater
==549555== Invalid write of size 8
==549555==    at 0x4026BD: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==549555==  Address 0x1ffe85eab8 is on thread 1's stack
==549555==  in frame #0, created by main (???:)
==549555==
Check number of arguments.
==549555==
==549555== HEAP SUMMARY:
==549555==     in use at exit: 0 bytes in 0 blocks
==549555==   total heap usage: 0 allocs, 0 frees, 0 bytes allocated
==549555==
==549555== All heap blocks were freed -- no leaks are possible
==549555==
==549555== For lists of detected and suppressed errors, rerun with: -s
==549555== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
```

## argc = 2
### if file does not exist
```bash
 % valgrind --leak-check=full ./so_long map/nosuchfile.ber
==550291== Memcheck, a memory error detector
==550291== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==550291== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==550291== Command: ./so_long map/nosuchfile.ber
==550291==
==550291== Warning: client switching stacks?  SP change: 0x1ffefffd10 --> 0x1ffe85eaa0
==550291==          to suppress, use: --max-stackframe=8000112 or greater
==550291== Invalid write of size 8
==550291==    at 0x4026D0: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550291==  Address 0x1ffe85ea98 is on thread 1's stack
==550291==  in frame #0, created by main (???:)
==550291==
==550291== Invalid write of size 8
==550291==    at 0x4025E0: init_data (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550291==    by 0x4026D4: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550291==  Address 0x1ffe85eaa0 is on thread 1's stack
==550291==  in frame #1, created by main (???:)
==550291==
==550291== Invalid write of size 8
==550291==    at 0x4025EB: init_data (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550291==    by 0x4026D4: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550291==  Address 0x1ffe85eaa8 is on thread 1's stack
==550291==  in frame #1, created by main (???:)
==550291==
==550291== Invalid write of size 8
==550291==    at 0x4025F7: init_data (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550291==    by 0x4026D4: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550291==  Address 0x1ffe85eab0 is on thread 1's stack
==550291==  in frame #1, created by main (???:)
==550291==
==550291== Invalid write of size 8
==550291==    at 0x402603: init_data (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550291==    by 0x4026D4: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550291==  Address 0x1ffe85eab8 is on thread 1's stack
==550291==  in frame #1, created by main (???:)
==550291==
==550291== Invalid write of size 8
==550291==    at 0x40260F: init_data (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550291==    by 0x4026D4: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550291==  Address 0x1ffe85eac0 is on thread 1's stack
==550291==  in frame #1, created by main (???:)
==550291==
==550291== Invalid write of size 8
==550291==    at 0x40261B: init_data (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550291==    by 0x4026D4: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550291==  Address 0x1ffe85eac8 is on thread 1's stack
==550291==  in frame #1, created by main (???:)
==550291==
==550291== Invalid write of size 8
==550291==    at 0x402626: init_data (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550291==    by 0x4026D4: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550291==  Address 0x1ffe85ead0 is on thread 1's stack
==550291==  in frame #1, created by main (???:)
==550291==
==550291== Invalid write of size 8
==550291==    at 0x402636: init_data (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550291==    by 0x4026D4: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550291==  Address 0x1ffe85ead8 is on thread 1's stack
==550291==  in frame #1, created by main (???:)
==550291==
==550291== Invalid write of size 4
==550291==    at 0x40263E: init_data (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550291==    by 0x4026D4: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550291==  Address 0x1ffe85eae0 is on thread 1's stack
==550291==  in frame #1, created by main (???:)
==550291==
==550291== Invalid write of size 4
==550291==    at 0x402649: init_data (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550291==    by 0x4026D4: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550291==  Address 0x1ffe85eae4 is on thread 1's stack
==550291==  in frame #1, created by main (???:)
==550291==
==550291== Invalid write of size 4
==550291==    at 0x402654: init_data (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550291==    by 0x4026D4: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550291==  Address 0x1ffe85eae8 is on thread 1's stack
==550291==  in frame #1, created by main (???:)
==550291==
==550291== Invalid write of size 4
==550291==    at 0x40265F: init_data (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550291==    by 0x4026D4: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550291==  Address 0x1ffe85eaec is on thread 1's stack
==550291==  in frame #1, created by main (???:)
==550291==
==550291== Invalid read of size 8
==550291==    at 0x402683: init_data (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550291==    by 0x4026D4: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550291==  Address 0x1ffe85ea98 is on thread 1's stack
==550291==  in frame #0, created by init_data (???:)
==550291==
==550291== Invalid write of size 8
==550291==    at 0x4026DC: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550291==  Address 0x1ffe85eac8 is on thread 1's stack
==550291==  in frame #0, created by main (???:)
==550291==
==550291== Invalid read of size 8
==550291==    at 0x402E34: read_img (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550291==    by 0x4026F5: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550291==  Address 0x1ffe85eac8 is on thread 1's stack
==550291==  in frame #1, created by main (???:)
==550291==
==550291== Invalid write of size 8
==550291==    at 0x402E4D: read_img (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550291==    by 0x4026F5: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550291==  Address 0x1ffe85eaa0 is on thread 1's stack
==550291==  in frame #1, created by main (???:)
==550291==
==550291== Invalid read of size 8
==550291==    at 0x402E54: read_img (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550291==    by 0x4026F5: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550291==  Address 0x1ffe85eac8 is on thread 1's stack
==550291==  in frame #1, created by main (???:)
==550291==
==550291== Invalid write of size 8
==550291==    at 0x402E6D: read_img (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550291==    by 0x4026F5: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550291==  Address 0x1ffe85eaa8 is on thread 1's stack
==550291==  in frame #1, created by main (???:)
==550291==
==550291== Invalid read of size 8
==550291==    at 0x402E75: read_img (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550291==    by 0x4026F5: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550291==  Address 0x1ffe85eac8 is on thread 1's stack
==550291==  in frame #1, created by main (???:)
==550291==
==550291== Invalid write of size 8
==550291==    at 0x402E8E: read_img (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550291==    by 0x4026F5: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550291==  Address 0x1ffe85eab0 is on thread 1's stack
==550291==  in frame #1, created by main (???:)
==550291==
==550291== Invalid read of size 8
==550291==    at 0x402E96: read_img (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550291==    by 0x4026F5: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550291==  Address 0x1ffe85eac8 is on thread 1's stack
==550291==  in frame #1, created by main (???:)
==550291==
==550291== Invalid write of size 8
==550291==    at 0x402EAF: read_img (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550291==    by 0x4026F5: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550291==  Address 0x1ffe85eab8 is on thread 1's stack
==550291==  in frame #1, created by main (???:)
==550291==
==550291== Invalid read of size 8
==550291==    at 0x402EB7: read_img (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550291==    by 0x4026F5: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550291==  Address 0x1ffe85eac8 is on thread 1's stack
==550291==  in frame #1, created by main (???:)
==550291==
==550291== Invalid write of size 8
==550291==    at 0x402ED0: read_img (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550291==    by 0x4026F5: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550291==  Address 0x1ffe85eac0 is on thread 1's stack
==550291==  in frame #1, created by main (???:)
==550291==
[FD ERROR]: No such file or directory
==550291==
==550291== HEAP SUMMARY:
==550291==     in use at exit: 94,369 bytes in 49 blocks
==550291==   total heap usage: 971 allocs, 922 frees, 911,103 bytes allocated
==550291==
==550291== 136 bytes in 1 blocks are definitely lost in loss record 32 of 48
==550291==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==550291==    by 0x40444F: mlx_init (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550291==    by 0x4026DB: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550291==
==550291== 224 (88 direct, 136 indirect) bytes in 1 blocks are definitely lost in loss record 38 of 48
==550291==    at 0x484DA83: calloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==550291==    by 0x405DDB: mlx_int_new_xshm_image (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550291==    by 0x406102: mlx_new_image (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550291==    by 0x4052D7: mlx_int_parse_xpm (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550291==    by 0x405711: mlx_xpm_file_to_image (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550291==    by 0x402DEB: load_img_in_mlx (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550291==    by 0x402E45: read_img (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550291==    by 0x4026F5: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550291==
==550291== 224 (88 direct, 136 indirect) bytes in 1 blocks are definitely lost in loss record 39 of 48
==550291==    at 0x484DA83: calloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==550291==    by 0x405DDB: mlx_int_new_xshm_image (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550291==    by 0x406102: mlx_new_image (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550291==    by 0x4052D7: mlx_int_parse_xpm (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550291==    by 0x405711: mlx_xpm_file_to_image (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550291==    by 0x402DEB: load_img_in_mlx (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550291==    by 0x402E65: read_img (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550291==    by 0x4026F5: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550291==
==550291== 224 (88 direct, 136 indirect) bytes in 1 blocks are definitely lost in loss record 40 of 48
==550291==    at 0x484DA83: calloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==550291==    by 0x405DDB: mlx_int_new_xshm_image (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550291==    by 0x406102: mlx_new_image (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550291==    by 0x4052D7: mlx_int_parse_xpm (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550291==    by 0x405711: mlx_xpm_file_to_image (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550291==    by 0x402DEB: load_img_in_mlx (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550291==    by 0x402E86: read_img (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550291==    by 0x4026F5: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550291==
==550291== 224 (88 direct, 136 indirect) bytes in 1 blocks are definitely lost in loss record 41 of 48
==550291==    at 0x484DA83: calloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==550291==    by 0x405DDB: mlx_int_new_xshm_image (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550291==    by 0x406102: mlx_new_image (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550291==    by 0x4052D7: mlx_int_parse_xpm (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550291==    by 0x405711: mlx_xpm_file_to_image (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550291==    by 0x402DEB: load_img_in_mlx (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550291==    by 0x402EA7: read_img (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550291==    by 0x4026F5: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550291==
==550291== 224 (88 direct, 136 indirect) bytes in 1 blocks are definitely lost in loss record 42 of 48
==550291==    at 0x484DA83: calloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==550291==    by 0x405DDB: mlx_int_new_xshm_image (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550291==    by 0x406102: mlx_new_image (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550291==    by 0x4052D7: mlx_int_parse_xpm (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550291==    by 0x405711: mlx_xpm_file_to_image (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550291==    by 0x402DEB: load_img_in_mlx (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550291==    by 0x402EC8: read_img (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550291==    by 0x4026F5: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550291==
==550291== LEAK SUMMARY:
==550291==    definitely lost: 576 bytes in 6 blocks
==550291==    indirectly lost: 680 bytes in 5 blocks
==550291==      possibly lost: 0 bytes in 0 blocks
==550291==    still reachable: 93,113 bytes in 38 blocks
==550291==         suppressed: 0 bytes in 0 blocks
==550291== Reachable blocks (those to which a pointer was found) are not shown.
==550291== To see them, rerun with: --leak-check=full --show-leak-kinds=all
==550291==
==550291== For lists of detected and suppressed errors, rerun with: -s
==550291== ERROR SUMMARY: 31 errors from 31 contexts (suppressed: 0 from 0)
```

### if file no permission
```bash
 % valgrind --leak-check=full ./so_long invalid.ber
==550431== Memcheck, a memory error detector
==550431== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==550431== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==550431== Command: ./so_long invalid.ber
==550431==
==550431== Warning: client switching stacks?  SP change: 0x1ffefffd10 --> 0x1ffe85eaa0
==550431==          to suppress, use: --max-stackframe=8000112 or greater
==550431== Invalid write of size 8
==550431==    at 0x4026D0: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550431==  Address 0x1ffe85ea98 is on thread 1's stack
==550431==  in frame #0, created by main (???:)
==550431==
==550431== Invalid write of size 8
==550431==    at 0x4025E0: init_data (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550431==    by 0x4026D4: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550431==  Address 0x1ffe85eaa0 is on thread 1's stack
==550431==  in frame #1, created by main (???:)
==550431==
==550431== Invalid write of size 8
==550431==    at 0x4025EB: init_data (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550431==    by 0x4026D4: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550431==  Address 0x1ffe85eaa8 is on thread 1's stack
==550431==  in frame #1, created by main (???:)
==550431==
==550431== Invalid write of size 8
==550431==    at 0x4025F7: init_data (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550431==    by 0x4026D4: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550431==  Address 0x1ffe85eab0 is on thread 1's stack
==550431==  in frame #1, created by main (???:)
==550431==
==550431== Invalid write of size 8
==550431==    at 0x402603: init_data (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550431==    by 0x4026D4: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550431==  Address 0x1ffe85eab8 is on thread 1's stack
==550431==  in frame #1, created by main (???:)
==550431==
==550431== Invalid write of size 8
==550431==    at 0x40260F: init_data (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550431==    by 0x4026D4: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550431==  Address 0x1ffe85eac0 is on thread 1's stack
==550431==  in frame #1, created by main (???:)
==550431==
==550431== Invalid write of size 8
==550431==    at 0x40261B: init_data (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550431==    by 0x4026D4: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550431==  Address 0x1ffe85eac8 is on thread 1's stack
==550431==  in frame #1, created by main (???:)
==550431==
==550431== Invalid write of size 8
==550431==    at 0x402626: init_data (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550431==    by 0x4026D4: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550431==  Address 0x1ffe85ead0 is on thread 1's stack
==550431==  in frame #1, created by main (???:)
==550431==
==550431== Invalid write of size 8
==550431==    at 0x402636: init_data (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550431==    by 0x4026D4: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550431==  Address 0x1ffe85ead8 is on thread 1's stack
==550431==  in frame #1, created by main (???:)
==550431==
==550431== Invalid write of size 4
==550431==    at 0x40263E: init_data (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550431==    by 0x4026D4: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550431==  Address 0x1ffe85eae0 is on thread 1's stack
==550431==  in frame #1, created by main (???:)
==550431==
==550431== Invalid write of size 4
==550431==    at 0x402649: init_data (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550431==    by 0x4026D4: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550431==  Address 0x1ffe85eae4 is on thread 1's stack
==550431==  in frame #1, created by main (???:)
==550431==
==550431== Invalid write of size 4
==550431==    at 0x402654: init_data (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550431==    by 0x4026D4: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550431==  Address 0x1ffe85eae8 is on thread 1's stack
==550431==  in frame #1, created by main (???:)
==550431==
==550431== Invalid write of size 4
==550431==    at 0x40265F: init_data (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550431==    by 0x4026D4: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550431==  Address 0x1ffe85eaec is on thread 1's stack
==550431==  in frame #1, created by main (???:)
==550431==
==550431== Invalid read of size 8
==550431==    at 0x402683: init_data (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550431==    by 0x4026D4: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550431==  Address 0x1ffe85ea98 is on thread 1's stack
==550431==  in frame #0, created by init_data (???:)
==550431==
==550431== Invalid write of size 8
==550431==    at 0x4026DC: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550431==  Address 0x1ffe85eac8 is on thread 1's stack
==550431==  in frame #0, created by main (???:)
==550431==
==550431== Invalid read of size 8
==550431==    at 0x402E34: read_img (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550431==    by 0x4026F5: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550431==  Address 0x1ffe85eac8 is on thread 1's stack
==550431==  in frame #1, created by main (???:)
==550431==
==550431== Invalid write of size 8
==550431==    at 0x402E4D: read_img (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550431==    by 0x4026F5: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550431==  Address 0x1ffe85eaa0 is on thread 1's stack
==550431==  in frame #1, created by main (???:)
==550431==
==550431== Invalid read of size 8
==550431==    at 0x402E54: read_img (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550431==    by 0x4026F5: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550431==  Address 0x1ffe85eac8 is on thread 1's stack
==550431==  in frame #1, created by main (???:)
==550431==
==550431== Invalid write of size 8
==550431==    at 0x402E6D: read_img (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550431==    by 0x4026F5: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550431==  Address 0x1ffe85eaa8 is on thread 1's stack
==550431==  in frame #1, created by main (???:)
==550431==
==550431== Invalid read of size 8
==550431==    at 0x402E75: read_img (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550431==    by 0x4026F5: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550431==  Address 0x1ffe85eac8 is on thread 1's stack
==550431==  in frame #1, created by main (???:)
==550431==
==550431== Invalid write of size 8
==550431==    at 0x402E8E: read_img (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550431==    by 0x4026F5: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550431==  Address 0x1ffe85eab0 is on thread 1's stack
==550431==  in frame #1, created by main (???:)
==550431==
==550431== Invalid read of size 8
==550431==    at 0x402E96: read_img (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550431==    by 0x4026F5: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550431==  Address 0x1ffe85eac8 is on thread 1's stack
==550431==  in frame #1, created by main (???:)
==550431==
==550431== Invalid write of size 8
==550431==    at 0x402EAF: read_img (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550431==    by 0x4026F5: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550431==  Address 0x1ffe85eab8 is on thread 1's stack
==550431==  in frame #1, created by main (???:)
==550431==
==550431== Invalid read of size 8
==550431==    at 0x402EB7: read_img (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550431==    by 0x4026F5: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550431==  Address 0x1ffe85eac8 is on thread 1's stack
==550431==  in frame #1, created by main (???:)
==550431==
==550431== Invalid write of size 8
==550431==    at 0x402ED0: read_img (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550431==    by 0x4026F5: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550431==  Address 0x1ffe85eac0 is on thread 1's stack
==550431==  in frame #1, created by main (???:)
==550431==
[FD ERROR]: Permission denied
==550431==
==550431== HEAP SUMMARY:
==550431==     in use at exit: 94,369 bytes in 49 blocks
==550431==   total heap usage: 971 allocs, 922 frees, 911,103 bytes allocated
==550431==
==550431== 136 bytes in 1 blocks are definitely lost in loss record 32 of 48
==550431==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==550431==    by 0x40444F: mlx_init (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550431==    by 0x4026DB: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550431==
==550431== 224 (88 direct, 136 indirect) bytes in 1 blocks are definitely lost in loss record 38 of 48
==550431==    at 0x484DA83: calloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==550431==    by 0x405DDB: mlx_int_new_xshm_image (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550431==    by 0x406102: mlx_new_image (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550431==    by 0x4052D7: mlx_int_parse_xpm (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550431==    by 0x405711: mlx_xpm_file_to_image (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550431==    by 0x402DEB: load_img_in_mlx (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550431==    by 0x402E45: read_img (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550431==    by 0x4026F5: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550431==
==550431== 224 (88 direct, 136 indirect) bytes in 1 blocks are definitely lost in loss record 39 of 48
==550431==    at 0x484DA83: calloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==550431==    by 0x405DDB: mlx_int_new_xshm_image (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550431==    by 0x406102: mlx_new_image (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550431==    by 0x4052D7: mlx_int_parse_xpm (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550431==    by 0x405711: mlx_xpm_file_to_image (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550431==    by 0x402DEB: load_img_in_mlx (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550431==    by 0x402E65: read_img (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550431==    by 0x4026F5: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550431==
==550431== 224 (88 direct, 136 indirect) bytes in 1 blocks are definitely lost in loss record 40 of 48
==550431==    at 0x484DA83: calloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==550431==    by 0x405DDB: mlx_int_new_xshm_image (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550431==    by 0x406102: mlx_new_image (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550431==    by 0x4052D7: mlx_int_parse_xpm (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550431==    by 0x405711: mlx_xpm_file_to_image (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550431==    by 0x402DEB: load_img_in_mlx (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550431==    by 0x402E86: read_img (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550431==    by 0x4026F5: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550431==
==550431== 224 (88 direct, 136 indirect) bytes in 1 blocks are definitely lost in loss record 41 of 48
==550431==    at 0x484DA83: calloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==550431==    by 0x405DDB: mlx_int_new_xshm_image (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550431==    by 0x406102: mlx_new_image (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550431==    by 0x4052D7: mlx_int_parse_xpm (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550431==    by 0x405711: mlx_xpm_file_to_image (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550431==    by 0x402DEB: load_img_in_mlx (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550431==    by 0x402EA7: read_img (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550431==    by 0x4026F5: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550431==
==550431== 224 (88 direct, 136 indirect) bytes in 1 blocks are definitely lost in loss record 42 of 48
==550431==    at 0x484DA83: calloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==550431==    by 0x405DDB: mlx_int_new_xshm_image (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550431==    by 0x406102: mlx_new_image (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550431==    by 0x4052D7: mlx_int_parse_xpm (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550431==    by 0x405711: mlx_xpm_file_to_image (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550431==    by 0x402DEB: load_img_in_mlx (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550431==    by 0x402EC8: read_img (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550431==    by 0x4026F5: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550431==
==550431== LEAK SUMMARY:
==550431==    definitely lost: 576 bytes in 6 blocks
==550431==    indirectly lost: 680 bytes in 5 blocks
==550431==      possibly lost: 0 bytes in 0 blocks
==550431==    still reachable: 93,113 bytes in 38 blocks
==550431==         suppressed: 0 bytes in 0 blocks
==550431== Reachable blocks (those to which a pointer was found) are not shown.
==550431== To see them, rerun with: --leak-check=full --show-leak-kinds=all
==550431==
==550431== For lists of detected and suppressed errors, rerun with: -s
==550431== ERROR SUMMARY: 31 errors from 31 contexts (suppressed: 0 from 0)
```

### if file has an error

#### map is empty
```bash
 % valgrind --leak-check=full ./so_long map/error/error_empty.ber
==550519== Memcheck, a memory error detector
==550519== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==550519== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==550519== Command: ./so_long map/error/error_empty.ber
==550519==
==550519== Warning: client switching stacks?  SP change: 0x1ffefffd00 --> 0x1ffe85ea90
==550519==          to suppress, use: --max-stackframe=8000112 or greater
==550519== Invalid write of size 8
==550519==    at 0x4026D0: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550519==  Address 0x1ffe85ea88 is on thread 1's stack
==550519==  in frame #0, created by main (???:)
==550519==
==550519== Invalid write of size 8
==550519==    at 0x4025E0: init_data (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550519==    by 0x4026D4: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550519==  Address 0x1ffe85ea90 is on thread 1's stack
==550519==  in frame #1, created by main (???:)
==550519==
==550519== Invalid write of size 8
==550519==    at 0x4025EB: init_data (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550519==    by 0x4026D4: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550519==  Address 0x1ffe85ea98 is on thread 1's stack
==550519==  in frame #1, created by main (???:)
==550519==
==550519== Invalid write of size 8
==550519==    at 0x4025F7: init_data (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550519==    by 0x4026D4: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550519==  Address 0x1ffe85eaa0 is on thread 1's stack
==550519==  in frame #1, created by main (???:)
==550519==
==550519== Invalid write of size 8
==550519==    at 0x402603: init_data (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550519==    by 0x4026D4: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550519==  Address 0x1ffe85eaa8 is on thread 1's stack
==550519==  in frame #1, created by main (???:)
==550519==
==550519== Invalid write of size 8
==550519==    at 0x40260F: init_data (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550519==    by 0x4026D4: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550519==  Address 0x1ffe85eab0 is on thread 1's stack
==550519==  in frame #1, created by main (???:)
==550519==
==550519== Invalid write of size 8
==550519==    at 0x40261B: init_data (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550519==    by 0x4026D4: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550519==  Address 0x1ffe85eab8 is on thread 1's stack
==550519==  in frame #1, created by main (???:)
==550519==
==550519== Invalid write of size 8
==550519==    at 0x402626: init_data (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550519==    by 0x4026D4: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550519==  Address 0x1ffe85eac0 is on thread 1's stack
==550519==  in frame #1, created by main (???:)
==550519==
==550519== Invalid write of size 8
==550519==    at 0x402636: init_data (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550519==    by 0x4026D4: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550519==  Address 0x1ffe85eac8 is on thread 1's stack
==550519==  in frame #1, created by main (???:)
==550519==
==550519== Invalid write of size 4
==550519==    at 0x40263E: init_data (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550519==    by 0x4026D4: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550519==  Address 0x1ffe85ead0 is on thread 1's stack
==550519==  in frame #1, created by main (???:)
==550519==
==550519== Invalid write of size 4
==550519==    at 0x402649: init_data (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550519==    by 0x4026D4: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550519==  Address 0x1ffe85ead4 is on thread 1's stack
==550519==  in frame #1, created by main (???:)
==550519==
==550519== Invalid write of size 4
==550519==    at 0x402654: init_data (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550519==    by 0x4026D4: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550519==  Address 0x1ffe85ead8 is on thread 1's stack
==550519==  in frame #1, created by main (???:)
==550519==
==550519== Invalid write of size 4
==550519==    at 0x40265F: init_data (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550519==    by 0x4026D4: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550519==  Address 0x1ffe85eadc is on thread 1's stack
==550519==  in frame #1, created by main (???:)
==550519==
==550519== Invalid read of size 8
==550519==    at 0x402683: init_data (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550519==    by 0x4026D4: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550519==  Address 0x1ffe85ea88 is on thread 1's stack
==550519==  in frame #0, created by init_data (???:)
==550519==
==550519== Invalid write of size 8
==550519==    at 0x4026DC: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550519==  Address 0x1ffe85eab8 is on thread 1's stack
==550519==  in frame #0, created by main (???:)
==550519==
==550519== Invalid read of size 8
==550519==    at 0x402E34: read_img (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550519==    by 0x4026F5: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550519==  Address 0x1ffe85eab8 is on thread 1's stack
==550519==  in frame #1, created by main (???:)
==550519==
==550519== Invalid write of size 8
==550519==    at 0x402E4D: read_img (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550519==    by 0x4026F5: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550519==  Address 0x1ffe85ea90 is on thread 1's stack
==550519==  in frame #1, created by main (???:)
==550519==
==550519== Invalid read of size 8
==550519==    at 0x402E54: read_img (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550519==    by 0x4026F5: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550519==  Address 0x1ffe85eab8 is on thread 1's stack
==550519==  in frame #1, created by main (???:)
==550519==
==550519== Invalid write of size 8
==550519==    at 0x402E6D: read_img (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550519==    by 0x4026F5: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550519==  Address 0x1ffe85ea98 is on thread 1's stack
==550519==  in frame #1, created by main (???:)
==550519==
==550519== Invalid read of size 8
==550519==    at 0x402E75: read_img (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550519==    by 0x4026F5: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550519==  Address 0x1ffe85eab8 is on thread 1's stack
==550519==  in frame #1, created by main (???:)
==550519==
==550519== Invalid write of size 8
==550519==    at 0x402E8E: read_img (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550519==    by 0x4026F5: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550519==  Address 0x1ffe85eaa0 is on thread 1's stack
==550519==  in frame #1, created by main (???:)
==550519==
==550519== Invalid read of size 8
==550519==    at 0x402E96: read_img (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550519==    by 0x4026F5: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550519==  Address 0x1ffe85eab8 is on thread 1's stack
==550519==  in frame #1, created by main (???:)
==550519==
==550519== Invalid write of size 8
==550519==    at 0x402EAF: read_img (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550519==    by 0x4026F5: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550519==  Address 0x1ffe85eaa8 is on thread 1's stack
==550519==  in frame #1, created by main (???:)
==550519==
==550519== Invalid read of size 8
==550519==    at 0x402EB7: read_img (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550519==    by 0x4026F5: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550519==  Address 0x1ffe85eab8 is on thread 1's stack
==550519==  in frame #1, created by main (???:)
==550519==
==550519== Invalid write of size 8
==550519==    at 0x402ED0: read_img (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550519==    by 0x4026F5: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550519==  Address 0x1ffe85eab0 is on thread 1's stack
==550519==  in frame #1, created by main (???:)
==550519==
[MAP ERROR]Map file is empty.
==550519==
==550519== HEAP SUMMARY:
==550519==     in use at exit: 102,369 bytes in 50 blocks
==550519==   total heap usage: 971 allocs, 921 frees, 917,650 bytes allocated
==550519==
==550519== 136 bytes in 1 blocks are definitely lost in loss record 32 of 49
==550519==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==550519==    by 0x40444F: mlx_init (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550519==    by 0x4026DB: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550519==
==550519== 224 (88 direct, 136 indirect) bytes in 1 blocks are definitely lost in loss record 38 of 49
==550519==    at 0x484DA83: calloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==550519==    by 0x405DDB: mlx_int_new_xshm_image (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550519==    by 0x406102: mlx_new_image (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550519==    by 0x4052D7: mlx_int_parse_xpm (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550519==    by 0x405711: mlx_xpm_file_to_image (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550519==    by 0x402DEB: load_img_in_mlx (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550519==    by 0x402E45: read_img (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550519==    by 0x4026F5: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550519==
==550519== 224 (88 direct, 136 indirect) bytes in 1 blocks are definitely lost in loss record 39 of 49
==550519==    at 0x484DA83: calloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==550519==    by 0x405DDB: mlx_int_new_xshm_image (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550519==    by 0x406102: mlx_new_image (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550519==    by 0x4052D7: mlx_int_parse_xpm (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550519==    by 0x405711: mlx_xpm_file_to_image (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550519==    by 0x402DEB: load_img_in_mlx (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550519==    by 0x402E65: read_img (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550519==    by 0x4026F5: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550519==
==550519== 224 (88 direct, 136 indirect) bytes in 1 blocks are definitely lost in loss record 40 of 49
==550519==    at 0x484DA83: calloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==550519==    by 0x405DDB: mlx_int_new_xshm_image (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550519==    by 0x406102: mlx_new_image (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550519==    by 0x4052D7: mlx_int_parse_xpm (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550519==    by 0x405711: mlx_xpm_file_to_image (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550519==    by 0x402DEB: load_img_in_mlx (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550519==    by 0x402E86: read_img (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550519==    by 0x4026F5: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550519==
==550519== 224 (88 direct, 136 indirect) bytes in 1 blocks are definitely lost in loss record 41 of 49
==550519==    at 0x484DA83: calloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==550519==    by 0x405DDB: mlx_int_new_xshm_image (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550519==    by 0x406102: mlx_new_image (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550519==    by 0x4052D7: mlx_int_parse_xpm (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550519==    by 0x405711: mlx_xpm_file_to_image (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550519==    by 0x402DEB: load_img_in_mlx (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550519==    by 0x402EA7: read_img (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550519==    by 0x4026F5: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550519==
==550519== 224 (88 direct, 136 indirect) bytes in 1 blocks are definitely lost in loss record 42 of 49
==550519==    at 0x484DA83: calloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==550519==    by 0x405DDB: mlx_int_new_xshm_image (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550519==    by 0x406102: mlx_new_image (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550519==    by 0x4052D7: mlx_int_parse_xpm (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550519==    by 0x405711: mlx_xpm_file_to_image (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550519==    by 0x402DEB: load_img_in_mlx (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550519==    by 0x402EC8: read_img (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550519==    by 0x4026F5: main (in /home/mfunakos/Desktop/42cursus/so_long/so_long)
==550519==
==550519== LEAK SUMMARY:
==550519==    definitely lost: 576 bytes in 6 blocks
==550519==    indirectly lost: 680 bytes in 5 blocks
==550519==      possibly lost: 0 bytes in 0 blocks
==550519==    still reachable: 101,113 bytes in 39 blocks
==550519==         suppressed: 0 bytes in 0 blocks
==550519== Reachable blocks (those to which a pointer was found) are not shown.
==550519== To see them, rerun with: --leak-check=full --show-leak-kinds=all
==550519==
==550519== For lists of detected and suppressed errors, rerun with: -s
==550519== ERROR SUMMARY: 31 errors from 31 contexts (suppressed: 0 from 0)
```

#### map doesnt have p

#### map doesnt have c

#### map doesnt have e

#### map isnt a rectangle

#### map format is invalid

#### player cant reach a goal

#### player cant reach all of c
