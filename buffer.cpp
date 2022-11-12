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

// TODO: Add your implementation of the buffer class here
//
//
   /**
     * @brief Construct a new Buffer object
     * @param size the size of the buffer
     */
    Buffer::Buffer(int size){
	   // buffer is fixed size, 
	   // but created dynamucally for 
	   // best class structure design
    	buffer = new buffer_item[size];
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
    bool Buffer ::insert_item(buffer_item item){
    	return true;
    }

    /**
     * @brief Remove an item from the buffer
     * @param item the item to remove
     * @return true if successful
     * @return false if not successful
     */
    bool Buffer:: remove_item(buffer_item *item){
    	return true;
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
    }
