//package Satori;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Iterator;
import java.util.ListIterator;

public class ArrayListSqrCloned<E> {
    private ArrayList<ArrayList<E>> list = new ArrayList<>();

    private ArrayList<E> clone(Collection<? extends E> c) {
        ArrayList<E> newList = new ArrayList<>();
        for (E item : c) {
            newList.add(item);
        }
        return newList;
    }

    public ArrayListSqrCloned() { }

    
    public ArrayListSqrCloned(Collection<? extends Collection<? extends E>> c) {
        for (Collection<? extends E> a : c) {
            list.add(clone(a));
        }
    }

    public ArrayList<E> get(int index) {
        return list.get(index);
    }

    public boolean contains(Object item) {
        return list.contains(item);
        // for (ArrayList<E> a : list) {
        //     if (a.equals(item)) {
        //         return true;
        //     }
        // }
        // return false;
    }

    public boolean containsAll(Collection<?> item) {
        return list.containsAll(item);
        // for (Collection<E> b : item) {
        //     boolean found = false;
        //     for (ArrayList<E> a : list) {
        //         if (a.equals(b)) {
        //             found = true;
        //             break;
        //         }
        //     }
        //     if (!found)
        //         return false;
        // }
        // return true;
    }


    public void clear() {
        list.clear();
    }

    public boolean add(Collection<? extends E> item) {
        ArrayList<E> clone = clone(item);
        return list.add(clone);
    }

    public void add(int index, Collection<? extends E> item) {
        ArrayList<E> clone = clone(item);
        list.add(index, clone);
    }

    public void addAll(int index, Collection<? extends Collection<? extends E>> c) {
        ArrayList<Collection<E>> al = new ArrayList<>();
        for (Collection<? extends E> item : c) {
            add(index++, item);
        }
    }

    public boolean addAll(Collection<? extends Collection<? extends E>> c) {
        addAll(size(), c);
        return c.size() > 0;
    }

    public void set(int index, Collection<? extends E> item) {
        ArrayList<E> clone = clone(item);
        list.set(index, clone);
    }

    public int lastIndexOf(Collection<? extends E> item) {
        return list.lastIndexOf(item);
    }

    public int indexOf(Collection<? extends E> item) {
        return list.indexOf(item);
        // int x = 0;
        // for (ArrayList<E> it : list) {
        //     if (item.equals(it)) {
        //         return x;
        //     }
        //     x++;
        // }
        // return -1;
    }

    public boolean isEmpty() {
        return list.isEmpty();
    }

    public int size() {
        return list.size();
    }

    public Iterator<ArrayList<E>> iterator() {
        return list.iterator();
    }

    public ListIterator<ArrayList<E>> listIterator() {
        return list.listIterator();
    }

    public ListIterator<ArrayList<E>> listIterator(int i) {
        return list.listIterator(i);
    }

    public ArrayList<E> remove(int index) {
        return list.remove(index);
    }

    public boolean remove(Collection<? extends E> item) {
        return list.remove(item);
    }

    public boolean removeAll(Collection<?> item) {
        return list.removeAll(item);
    }

    public int hashCode() {
        return list.hashCode();
    }

    @Override
    public boolean equals(Object item) {
        if (item instanceof ArrayList) {
            ArrayList<?> al = (ArrayList<?>) item;
            return al.equals(list);
        }
        if (item instanceof ArrayListSqrCloned) {
            ArrayListSqrCloned<?> al = (ArrayListSqrCloned<?>) item;
            return al.list.equals(list);
        }
        return false;
    }
}