using System;
using System.Collections.Generic;
using static System.Console;
public class Node {
    public Node left;
    public Node right;
    public int Data { get; }
    public Node(int num) {
        Data = num;
    }
    public void JudgeAndLink(Node judge,Node linker) {
        if (right == judge) right = linker;
        else left = linker;
    }
    public Node BSTFind(int num) {
        Node current = this;
        while (current!=null) {
            switch (num.CompareTo(current.Data)) {
                case 1:
                    current = current.right;
                    break;
                case -1:
                    current = current.left;
                    break;
                case 0:
                    return current;
            }
        }
        return null;
    }
    public void BSTInsert(Node n) {
        Node current = this;
        while (!((n.Data< current.Data && current.left==null)||(n.Data>current.Data&&current.right==null))) {
            if (n.Data > current.Data) current = current.right;
            else if (n.Data < current.Data) current = current.left;
            else break;
        }
        if (n.Data > current.Data) current.right = n;
        else if (n.Data < current.Data) current.left=n;
    }
    public bool BSTDelete(int n) {
        if (Data == n) return true;
        Node currentParent = null, current = this;
        while (current != null) {
            switch (n.CompareTo(current.Data)) {
                case 1:
                    currentParent = current;
                    current = current.right;
                    break;
                case -1:
                    currentParent = current;
                    current = current.left;
                    break;
                case 0:
                    if (current.left != null && current.right != null) {
                        Node rightMin = current.right, rightMinParent = current;
                        while (rightMin.left!=null) {
                            rightMinParent = rightMin;
                            rightMin = rightMin.left;
                        }
                        if (rightMinParent != current) {
                            rightMinParent.left = rightMin.right;
                            rightMin.right = current.right;
                        }
                        rightMin.left = current.left;
                        currentParent.JudgeAndLink(current, rightMin);
                    }
                    else if (current.right != null) currentParent.JudgeAndLink(current, current.right);
                    else currentParent.JudgeAndLink(current, current.left);
                    current = null;
                    break;
            }
        }
        return false;
    }
}
public sealed class Program {
    static void Traversal(Node n) {
        if (n == null) return;
        Traversal(n.left);
        Traversal(n.right);
        Write(n.Data + " ");
    }
    static void StackTraversal(Node n) {
        var stack = new Stack<Node>();
        while (stack.Count!=0||n!=null) {
            while (n!=null) {
                stack.Push(n);
                //Write($"{n.num}-");//先序遍历
                n = n.left;
            }
            if (stack.Count != 0) {
                n=stack.Pop();
                Write(n.Data+" ");//中序遍历
                n = n.right;
                }
            }
        }
    static void HardTraversal(Node n) {//Post Order
        var stack = new Stack<Node>();
        var checkedNodes = new Stack<Node>();
        while (n!=null||stack.Count!=0) {
            while (n!=null) {
                stack.Push(n);
                n = n.left;
             }
             n = stack?.Peek();
             if (n.right!=null) {
                 if (checkedNodes.Count != 0) {
                        if (n != checkedNodes.Peek()) {
                            checkedNodes.Push(n);
                            n = n.right;
                        }
                        else {
                            Write(stack.Pop().Data+" ");
                            n = null;
                            checkedNodes.Pop();
                        }
                    }
                 else {
                        checkedNodes.Push(n);
                        n = n.right;
                 }
             }
             else {
                    Write(stack.Pop().Data+" ");
                    n = null;
             }
        }
    }
    static void LevelOrderTraversal(Node n) {
        if (n == null) return;
        var queue = new Queue<Node>();
        queue.Enqueue(n);
        while (queue.Count!=0) {
            Node temp = queue.Dequeue();
            if (temp.left != null) queue.Enqueue(temp.left);
            if (temp.right != null) queue.Enqueue(temp.right);
            Write(temp.Data + " ");
        }
    }
    static void Main(string[] args) {
        Node n = new Node(7) {
            left = new Node(5), 
            right = new Node(9)
        };
        n.left.left = new Node(3);
        n.right.right = new Node(10);
        n.right.left = new Node(8);
        LevelOrderTraversal(n);
        WriteLine();
        n.BSTInsert(new Node(2));
        n.BSTDelete(9);
        n.BSTDelete(3);
        n.BSTInsert(new Node(11));
        LevelOrderTraversal(n);
    }
}
