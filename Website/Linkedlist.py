class Node:
    def __init__(self, data):
        self.data = data
        self.next = None

class LinkedList:
    def __init__(self):
        self.head = None
    
    def add_at_start(self, data):
        new_node = Node(data)
        new_node.next = self.head
        self.head = new_node
    
    def add_at_end(self, data):
        new_node = Node(data)
        if not self.head:
            self.head = new_node
            return
        current = self.head
        while current.next:
            current = current.next
        current.next = new_node
    
    def remove_from_start(self):
        if self.head:
            self.head = self.head.next
    
    def remove_from_end(self):
        if not self.head:
            return
        if not self.head.next:
            self.head = None
            return
        current = self.head
        while current.next.next:
            current = current.next
        current.next = None
    
    def add_at_position(self, data, position):
        new_node = Node(data)
        if position == 0:
            new_node.next = self.head
            self.head = new_node
            return
        current = self.head
        for _ in range(position - 1):
            if not current:
                return
            current = current.next
        if current:
            new_node.next = current.next
            current.next = new_node
    
    def remove_two_nodes(self, pos1, pos2):
        for pos in sorted([pos1, pos2], reverse=True):
            current = self.head
            if pos == 0:
                self.head = self.head.next
                continue
            for _ in range(pos - 1):
                if not current:
                    return
                current = current.next
            if current and current.next:
                current.next = current.next.next
    
    def detect_loop(self):
        slow = self.head
        fast = self.head
        while fast and fast.next:
            slow = slow.next
            fast = fast.next.next
            if slow == fast:
                return True
        return False
    
    def reverse(self):
        prev = None
        current = self.head
        while current:
            next_node = current.next
            current.next = prev
            prev = current
            current = next_node
        self.head = prev
    
    def find_duplicates(self):
        seen = set()
        duplicates = set()
        current = self.head
        while current:
            if current.data in seen:
                duplicates.add(current.data)
            seen.add(current.data)
            current = current.next
        return duplicates
    
    def display(self):
        current = self.head
        while current:
            print(current.data, end=" -> ")
            current = current.next
        print("None")


ll = LinkedList()
ll.add_at_start(3)
ll.add_at_start(2)
ll.add_at_start(1)
ll.add_at_end(4)
ll.add_at_position(5, 2)
ll.display() 
ll.remove_from_start()
ll.display() 
ll.remove_from_end()
ll.display() 