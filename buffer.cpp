/**
* Assignment 4: Producer Consumer Problem
 * @file buffer.cpp
 * @author Jordan Aquino & Jamison Coombs
 * @brief Implementation file for the buffer class
 * @version 0.1
 */

//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code
#include "buffer.h"
#include <iostream>

// TODO: Add your implementation of the buffer class here
//
//
   /**
     * @brief Construct a new Buffer object
     * @param size the size of the buffer
     */
    Buffer::Buffer(int size){
	   // buffer is fixed size, 
	   // but created dynamically for 
	   // best class structure design
    	buffer = new buffer_item[size];
      capacity = size;
    }

    Buffer::Buffer(const Buffer& b1)
    {
      capacity = b1.capacity;
      buffer = new buffer_item[capacity];
    }

    /**
     * @brief Destroy the Buffer object
     */
    Buffer::~Buffer(){
	    delete[] buffer;
    }

    /**
     * @brief Insert an item into the buffer
     * @param item the item to insert
     * @return true if successful
     * @return false if not successful
     */
    bool Buffer::insert_item(buffer_item item){
      if(count != capacity)
      {
        buffer[count++] = item;
    	  return true;
      }
      return false;
    }

    /**
     * @brief Remove an item from the buffer
     * @param item the item to remove
     * @return true if successful
     * @return false if not successful
     */
    buffer_item Buffer:: remove_item(){
      if(count > 0)
      {
    	  buffer_item res = buffer[0];
        for(int i = 0; i < capacity-1; i++)
          buffer[i] = buffer[i+1];

        count--;
        return res;
      }
      return -1;
    }

    /**
     * @brief Get the size of the buffer
     * @return the size of the buffer
     */
    int Buffer:: get_size(){ //size means capacity in this context
    	return capacity;	
    }

    /**
     * @brief Get the number of items in the buffer
     * @return the number of items in the buffer
     */
    int Buffer:: get_count(){
    	return count;	
    }

    /**
     * @brief Check if the buffer is empty
     * @return true if the buffer is empty, else false
     */
    bool Buffer::is_empty(){
    	return (count == 0);
    }
    /**
     * @brief Check if the buffer is full
     * @return true if the buffer is full, else false
     */
    bool Buffer:: is_full(){
	    // since I assume count will be utilized for indexing purposes.
	    // Recall that array[4] is the 5-th element for array with 5 elements. 
    	return(count >= capacity );
    }
    
    /**
     *@brief prints buffer
     *
     */
    void Buffer:: print_buffer(){
      std::cout << "Buffer: [";
      for(int i = 0; i < count; i++)
      {
        std::cout << buffer[i];
        if (i != count-1)
          std::cout << ", ";
      }
      std::cout << "]\n";
    }
