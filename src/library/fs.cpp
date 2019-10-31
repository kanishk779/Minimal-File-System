// fs.cpp: File System

#include "sfs/fs.h"

#include <algorithm>

#include <assert.h>
#include <stdio.h>
#include <string.h>

// Debug file system -----------------------------------------------------------

void
FileSystem::debug(Disk* disk)
{
  Block block;

  // Read Superblock
  disk->read(0, block.Data);
  if(block.Super.MagicNumber != 0xf0f03410)
  {  
    char what[BUFSIZ];
    snprintf(what, BUFSIZ, "This is not a valid FileSystem - %s",strerror(errno));
    throw std::runtime_error(what);
  }
  printf("SuperBlock:\n");
  printf("    The MagicNumber is valid\n");
  printf("    %u blocks\n", block.Super.Blocks);
  printf("    %u inode blocks\n", block.Super.InodeBlocks);
  printf("    %u inodes\n", block.Super.Inodes);

  // Read Inode blocks
  uint32_t inode_count = 1;
  for(int i=1;i <= block.Super.InodeBlocks;i++)
  {
    // now we get hold of each of the INODE_BLOCK
    disk->read(i,block.Data);

    // Looping through all the inodes in this block
    for(int j=0;j<INODES_PER_BLOCK;j++)
    {
      Inode current_inode = block.Inodes[j];
      int valid_direct_pointers = 0;
      if(current_inode->valid)
      {
        // increase the valid direct pointer count
        for(int k=0;k<POINTERS_PER_INODE;k++)
        {
          if(current_inode->Direct[k] != 0)
            valid_direct_pointers += 1;
        }
        printf("Inode %u\n",inode_count );
        printf("    size: %u\n",current_inode->Size);
        printf("    direct Blocks: %d\n",valid_direct_pointers);
      }
    }
  }
}

// Format file system ----------------------------------------------------------

bool
FileSystem::format(Disk* disk)
{
  // check if the disk is already mounted -> if so than do nothing
  if(disk->mounted())
  {
    printf("The disk is already mounted!! cannot format\n");
    return false;
  }
  // Write superblock
  Block block;
  disk->read(0,block.Data);
  block.Super.MagicNumber = 0xf0f03410;
  block.Super.
  // Clear all other blocks
  return true;
}

// Mount file system -----------------------------------------------------------

bool
FileSystem::mount(Disk* disk)
{
  // Read superblock

  // Set device and mount

  // Copy metadata

  // Allocate free block bitmap

  return true;
}

// Create inode ----------------------------------------------------------------

ssize_t
FileSystem::create()
{
  // Locate free inode in inode table

  // Record inode if found
  return 0;
}

// Remove inode ----------------------------------------------------------------

bool
FileSystem::remove(size_t inumber)
{
  // Load inode information

  // Free direct blocks

  // Free indirect blocks

  // Clear inode in inode table
  return true;
}

// Inode stat ------------------------------------------------------------------

ssize_t
FileSystem::stat(size_t inumber)
{
  // Load inode information
  return 0;
}

// Read from inode -------------------------------------------------------------

ssize_t
FileSystem::read(size_t inumber, char* data, size_t length, size_t offset)
{
  // Load inode information

  // Adjust length

  // Read block and copy to data
  return 0;
}

// Write to inode --------------------------------------------------------------

ssize_t
FileSystem::write(size_t inumber, char* data, size_t length, size_t offset)
{
  // Load inode

  // Write block and copy to data
  return 0;
}
