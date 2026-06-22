class Node:
    def __init__(self, data):
        self.data = data
        self.next = None

class LinkedList:
    def __init__(self):
        self.head = None

    def add_end(self, data):
        new_node = Node(data)
        if self.head is None:
            self.head = new_node
            return
        last_node = self.head
        while last_node.next:
            last_node = last_node.next
        last_node.next = new_node
    def add_beginning(self, data):
        new_node = Node(data)
        new_node.next = self.head
        self.head = new_node


    def display(self):
        current_node = self.head
        while current_node:
            print(current_node.data, end=" -> ")
            current_node = current_node.next
        print("None")

ll = LinkedList()  
ll.add_end(100)
ll.add_end(150)
ll.add_end(350)
ll.add_end(400)
ll.add_end(450)
ll.add_beginning(50)    
ll.add_beginning(25)
ll.display()