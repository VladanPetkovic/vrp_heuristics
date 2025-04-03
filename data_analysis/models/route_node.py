class RouteNode:
    def __init__(self, node_id, next_node_id, x, y, quantity):
        self.node_id = node_id
        self.next_node_id = next_node_id
        self.x = x
        self.y = y
        self.quantity = quantity

    def __repr__(self):
        return f"RouteNode(id={self.node_id}, next_node_id={self.next_node_id}, x={self.x}, y={self.y}, quantity={self.quantity})"
