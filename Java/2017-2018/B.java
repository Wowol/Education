//package Satori;

// WARNING! Please read the task before judging this code! :)

import java.awt.print.Book;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Iterator;
import java.util.List;

public class a implements Iterable<a> {

    public Iterator<a> iterator() {
        Iterator<a> it = new Iterator<a>() {

            private int currentIndex = 0;
            {
                if (p) {
                    Collections.sort(sorted);
                }
            }

            @Override
            public boolean hasNext() {
                return currentIndex < list.size();
            }

            @Override
            public a next() {
                Integer q = !p ? list.get(currentIndex++) : sorted.get(currentIndex++);
                a w = new a(true);
                w.a(q);
                return w;
            }

            @Override
            public void remove() {
                throw new UnsupportedOperationException();
            }
        };
        return it;
    }

    public a(boolean oneElement) {
        this();
        this.oneElement = true;
    }

    public a() {
        list = new ArrayList<Integer>();
        sorted = new ArrayList<>();
        this.a = new a(this);
        p = false;
    }

    public a(a old) {
        this.a = old;
        p = true;
        list = old.list;
        sorted = old.sorted;
    }

    List<Integer> list;
    List<Integer> sorted;
    boolean p;
    boolean oneElement = false;

    public a a;

    public a a(int number) {
        list.add(number);
        sorted.add(number);

        return p == true ? a : this;
    }

    public Integer a() {
        Integer q = list.get(list.size() - 1);
        list.remove(list.size() - 1);
        sorted.remove(q);
        return q;
    }

    public a a(Integer number) {
        list.add(0, number);
        sorted.add(number);
        return p == true ? this : a;
    }

    @Override
    public String toString() {
        if (oneElement) {
            return list.get(0).toString();
        }
        if (!p) {
            Collections.sort(sorted);
            return sorted.toString();
        } else {
            return list.toString();
        }

    }

}