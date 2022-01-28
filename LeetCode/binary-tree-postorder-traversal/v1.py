# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def postorderTraversal(self, root: Optional[TreeNode]) -> List[int]:
        pot = []
        if root == None:
            return pot
        if root.left != None:
            pot = self.postorderTraversal(root.left)
        if root.right != None:
            pot =  pot + self.postorderTraversal(root.right)
        if root.val == None:
            return []
        pot.append(root.val)
        return pot