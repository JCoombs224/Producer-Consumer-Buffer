/**
* Assignment 4: Producer Consumer Problem
 * @file buffer.h
 * @author Jordan Aquino & Jamison Coombs
 * @brief header file for the buffer class
 * @version 0.1
 */

#ifndef ASSIGN4_BUFFER_H
#define ASSIGN4_BUFFER_H

// Define the data type of the buffer items
typedef int buffer_item;

/**
 * @brief The bounded buffer class. The number of items in the buffer cannot exceed the size of the buffer.
 */
class Buffer {
private:
    // Add your implementation of the buffer class here
	buffer_item *buffer;		// Pointer to fixed size array of buffer items . 
	int capacity;			// limit of items in buffer at a time
	int count = 0;			// number of items in the buffer. Initialized to zero.
public:
    /**
     * @brief Construct a new Buffer object
     * @param size the size of the buffer
     */
    Buffer(int size = 5);

    Buffer(const Buffer& b1);

    Buffer& operator=(Buffer const &rhs)
    {
        if(&rhs != this)
        {
            delete[] buffer;
            capacity = rhs.capacity;
            count = 0;
            buffer = new buffer_item[capacity];
        }
        return *this;
    }

    /**
     * @brief Destroy the Buffer object
     */
    ~Buffer();

    /**
     * @brief Insert an item into the buffer
     * @param item the item to insert
     * @return true if successful
     * @return false if not successful
     */
    bool insert_item(buffer_item item);

    /**
     * @brief Remove an item from the buffer
     * @param item the item to remove
     * @return true if successful
     * @return false if not successful
     */
    buffer_item remove_item();

    /**
     * @brief Get the size of the buffer
     * @return the size of the buffer
     */
    int get_size();

    /**
     * @brief Get the number of items in the buffer
     * @return the number of items in the buffer
     */
    int get_count();

    /**
     * @brief Chceck if the buffer is empty
     * @return true if the buffer is empty, else false
     */
    bool is_empty();
    /**
     * @brief Check if the buffer is full
     * @return true if the buffer is full, else false
     */
    bool is_full();

    /**
     * @brief Print the buffer
     */
    void print_buffer();
};
#endif //ASSIGN4_BUFFER_H
