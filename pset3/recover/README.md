# Recover

this is a program that recovers JPEGs from a memory card.

## Background

Pictures stored on digital cameras are usually contiguous on memmory cards. When pictures are "deleted", there is a chance that they can still be recovered if certain patterns are found.

For JPEG file, the first three bytes are 
```
0xff 0xd8 0xff
```

The fourth byte is one of these: `0xe0`, `0xe1`, `0xe2`, `0xe3`, `0xe4`, `0xe5`, `0xe6`, `0xe7`, `0xe8`, `0xe9`, `0xea`, `0xeb`, `0xec`, `0xed`, `0xee`, `0xef`, meaning that the first four bits are `1110`.

Digital cameras also usually initialize cards with a FAT file system with 512 bytes of every block. It means that the signiture of JPEG file is always in the beginning of the block. 

