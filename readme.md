# BLG 413E - Assignment 2
İrem Nur Demirtaş | 150150302

## Information
Kernel version: 3.13.0

## Compilation and Running
1. Copy the kernel source. 
2. Replace the files in the kernel source with the ones in the repository.
3. Follow the instructions in PS2.

## Test
test/ directory contains a test program. The test proceeds as follows:
1. Parent creates a child.
2. The child reports its status and exits.
3. Parent's nice_inc is updated.
4. Parent creates another child and waits.
5. The child reports its status and waits.
6. The child creates two grandchildren.
7. Parent exits.
8. OPTIONAL: nice_inc of the new parent is altered.
9. The child reports its status.
10. The grandchildren report their statuses.

### Compilation
``` gcc test.c -o test ```

### Running
If the reaper is known beforehand:

``` ./test <parent_pid> <parent_nice_inc> <new_parent> <new_parent_nice_inc>```

If the reaper is not known:

``` ./test <parent_pid> <parent_nice_inc>```

## Diff Files
Diff files can be found in diff/ directory.