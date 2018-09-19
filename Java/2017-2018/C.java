//package Satori;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Iterator;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.ListIterator;
import java.util.Map;
import java.util.NoSuchElementException;
import java.util.Objects;
import java.util.Set;
import java.util.function.UnaryOperator;

public class ListIsFunction {
    private LinkedHashMap<Integer, Object> map = new LinkedHashMap<>();
    private ArrayList<Object> list = new ArrayList<>();

    public List asList() {
        return new List<Object>() {

            // Tested
            @Override
            public boolean equals(Object o) {
                return list.equals(o);
            }

            // Tested (nie, ale powinno dzialac)
            @Override
            public int hashCode() {
                return list.hashCode();
            }

            // Tested            
            @Override
            public void add(int index, Object obj) {
                if (index < 0)
                {
                    throw new ArrayIndexOutOfBoundsException();
                }
                if (index > size()) {
                    throw new IndexOutOfBoundsException();
                }

                list.add(index, obj);

                Object oldTemp = obj;
                for (int x = index; x < map.size(); x++) {
                    Object temp = map.remove(x);
                    map.put(x, oldTemp);
                    oldTemp = temp;
                }
                map.put(map.size(), oldTemp);
            }

            // Tested            
            @Override
            public boolean add(Object obj) {
                add(list.size(), obj);
                return true;
            }

            // Tested
            @Override
            public boolean addAll(Collection<? extends Object> c) {
                return addAll(list.size(), c);
            }

            /// To moze dzialac za wolno, teraz dziala jakos w n^2
            // Tested
            @Override
            public boolean addAll(int index, Collection<? extends Object> c) throws UnsupportedOperationException {
                if (c == null) {
                    throw new NullPointerException();
                }

                if (index < 0 || index > size()) {
                    throw new IndexOutOfBoundsException();
                }

                Object[] a = c.toArray();

                int s = a.length;
                if (s == 0)
                    return false;

                for (Object o : a) {
                    add(index++, o);
                }
                return true;
            }

            // Tested
            @Override
            public void clear() {
                list.clear();
                map.clear();
            }

            // Tested
            @Override
            public int size() {
                return list.size();
            }

            // Tested
            @Override
            public boolean isEmpty() {
                return list.isEmpty();
            }

            // Tested
            @Override
            public boolean contains(Object o) {
                return list.contains(o);
            }

            // Tested (nie, ale powinno dzialac)
            @Override
            public Object[] toArray() {
                return list.toArray();
            }

            // Tested (nie, ale powinno dzialac)
            @Override
            public <T> T[] toArray(T[] a) {
                if (a == null) {
                    throw new NullPointerException();
                }
                return list.toArray(a);
            }

            // Tested
            @Override
            public boolean remove(Object o) {
                int ind = indexOf(o);
                if (ind == -1) {
                    return false;
                }
                remove(ind);
                return true;
            }

            // Tested
            @Override
            public Object remove(int index) {
                if (index < 0 || index >= size()) {
                    throw new IndexOutOfBoundsException();
                }
                map.remove(index);
                for (int x = index + 1; x <= map.size(); x++) {
                    Object temp = map.remove(x);
                    map.put(x - 1, temp);
                }
                return list.remove(index);
            }

            // Tested (nie, ale powinno dzialac)
            @Override
            public boolean containsAll(Collection<?> c) {
                if (c == null) {
                    throw new NullPointerException();
                }
                return list.containsAll(c);
            }

            // Tested
            @Override
            public boolean removeAll(Collection<?> c) {
                boolean changed = false;
                boolean tempChanged = false;

                do {
                    tempChanged = false;
                    for (Object o : c) {
                        if (remove(o)) {
                            changed = true;
                            tempChanged = true;
                        }
                    }
                } while (tempChanged);

                return changed;
            }

            // Tested
            @Override
            public boolean retainAll(Collection<?> c) {
                boolean changed = false;
                Object[] array = list.toArray();
                for (Object o : array) {
                    if (!c.contains(o)) {
                        if (remove(o)) {
                            changed = true;
                        }
                    }
                }
                return changed;
            }

            // Tested
            @Override
            public Object get(int index) {
                return list.get(index);
            }

            // Tested
            @Override
            public Object set(int index, Object element) {
                if (index < 0 || index >= size()) {
                    throw new IndexOutOfBoundsException();
                }
                map.put(index, element);
                return list.set(index, element);
            }

            // Tested
            @Override
            public int indexOf(Object o) {
                return list.indexOf(o);
            }

            // Tested
            @Override
            public int lastIndexOf(Object o) {
                return list.lastIndexOf(o);
            }

            // Tested
            @Override
            public Iterator<Object> iterator() {
                return listIterator();
            }

            // Tested
            @Override
            public ListIterator<Object> listIterator() {
                return listIterator(0);
            }

            // Tested, ale moze nie dzialac xddddd
            @Override
            public ListIterator<Object> listIterator(int index) {
                if (index < 0 || index > size()) {
                    throw new IndexOutOfBoundsException();
                }
                return new ListIterator<Object>() {
                    int cursor = index;
                    int lastRet = -1;

                    public boolean hasNext() {
                        return cursor != list.size();
                    }

                    public Object next() {
                        int i = cursor;
                        if (i >= list.size())
                            throw new NoSuchElementException();
                        cursor = i + 1;

                        return list.get(lastRet = i);
                    }

                    public boolean hasPrevious() {
                        return cursor != 0;
                    }

                    public Object previous() {
                        int i = cursor - 1;
                        if (i < 0)
                            throw new NoSuchElementException();
                        cursor = i;
                        return list.get(lastRet = i);
                    }

                    public int nextIndex() {
                        return cursor;
                    }

                    public int previousIndex() {
                        return cursor - 1;
                    }

                    public void remove() {
                        if (lastRet < 0)
                            throw new IllegalStateException();

                        ListIsFunction.this.asList().remove(lastRet);
                        cursor = lastRet;
                        lastRet = -1;
                    }

                    public void set(Object e) {
                        if (lastRet < 0)
                            throw new IllegalStateException();

                        ListIsFunction.this.asList().set(lastRet, e);
                    }

                    public void add(Object e) {
                        int i = cursor;
                        ListIsFunction.this.asList().add(i, e);
                        cursor = i + 1;
                        lastRet = -1;
                    }

                };
            }

            /// tutaj moze cos byc
            @Override
            public List<Object> subList(int fromIndex, int toIndex) {
                return list.subList(fromIndex, toIndex);
            }

            // Tested
            @Override
            public String toString() {
                return list.toString();
            }

        };
    }

    public Map<Integer, Object> asMap() {
        return new Map<Integer, Object>() {

            // Tested
            @Override
            public int size() {
                return map.size();
            }

            // Tested
            @Override
            public boolean isEmpty() {
                return map.isEmpty();
            }

            // Tested
            @Override
            public boolean containsKey(Object key) {
                if (key == null) {
                    throw new NullPointerException();
                }
                return map.containsKey(key);
            }

            // Tested
            @Override
            public boolean containsValue(Object value) {
                return map.containsValue(value);
            }

            // Tested
            @Override
            public Object get(Object key) {
                if (key == null) {
                    throw new NullPointerException();
                }
                return map.get(key);
            }

            // Tested (nie, ale raczej dziala)
            @Override
            public int hashCode() {
                return map.hashCode();
            }

            // Tested
            @Override
            public Object put(Integer key, Object value) {
                if (key == null) {
                    throw new NullPointerException();
                }
                if (list.size() == key) {
                    list.add(value);
                } else if (list.size() > key && key >= 0)
                    list.set(key, value);
                else {
                    throw new IllegalArgumentException();
                }
                return map.put(key, value);
            }

            // Tested
            @Override
            public void putAll(Map<? extends Integer, ? extends Object> m) {
                if (m == null) {
                    throw new NullPointerException();
                }
                for (Map.Entry<? extends Integer, ? extends Object> e : m.entrySet()) {
                    Integer key = e.getKey();
                    if (key == null) {
                        throw new NullPointerException();
                    }
                }

                for (Map.Entry<? extends Integer, ? extends Object> e : m.entrySet()) {
                    Integer key = e.getKey();
                    Object value = e.getValue();
                    try {
                        put(key, value);
                    } catch (Exception f) {
                    }
                }

            }

            // Tested
            @Override
            public Object remove(Object key) {
                if (key == null) {
                    throw new NullPointerException();
                }
                if (!(key instanceof Integer)) {
                    throw new ClassCastException();
                }

                if ((int) key >= list.size() || (int) key < 0) {
                    return null;
                }

                if ((int) key == list.size() - 1) {
                    list.remove((int) key);
                    return map.remove(key);
                } else {
                    throw new IllegalArgumentException();
                }
            }

            // Tested
            @Override
            public boolean equals(Object o) {
                return map.equals(o);
            }

            // Tested
            @Override
            public void clear() {
                map.clear();
                list.clear();
            }

            // Tutaj moze cos
            // Tested
            @Override
            public Set<Integer> keySet() {
                return new Set<Integer>() {
                    Set<Integer> ks = map.keySet();
                    Iterator it = ks.iterator();

                    @Override
                    public int size() {
                        return ks.size();
                    }

                    @Override
                    public boolean isEmpty() {
                        return ks.isEmpty();
                    }

                    @Override
                    public boolean contains(Object o) {
                        return ks.contains(o);
                    }

                    @Override
                    public Iterator<Integer> iterator() {
                        return new Iterator<Integer>() {

                            @Override
                            public boolean hasNext() {
                                return it.hasNext();
                            }

                            @Override
                            public Integer next() {
                                return (Integer) it.next();
                            }

                            @Override
                            public void remove() {
                                if (!hasNext()) {
                                    ListIsFunction.this.asList().remove(list.size() - 1);
                                } else {
                                    throw new java.lang.IllegalStateException();
                                }
                            }

                        };
                    }

                    @Override
                    public Object[] toArray() {
                        return ks.toArray();
                    }

                    @Override
                    public <T> T[] toArray(T[] a) {
                        return ks.toArray(a);
                    }

                    @Override
                    public boolean add(Integer e) {
                        throw new UnsupportedOperationException();
                    }

                    @Override
                    public boolean remove(Object o) {
                        if (!containsKey(o)) {
                            return false;
                        }
                        ListIsFunction.this.asMap().remove((Integer) o);
                        return true;
                    }

                    @Override
                    public boolean containsAll(Collection<?> c) {
                        return ks.containsAll(c);
                    }

                    @Override
                    public boolean addAll(Collection<? extends Integer> c) {
                        throw new UnsupportedOperationException();
                    }

                    // Nie wiem
                    @Override
                    public boolean retainAll(Collection<?> c) {
                        throw new UnsupportedOperationException();
                    }

                    // Nie wiem
                    @Override
                    public boolean removeAll(Collection<?> c) {
                        throw new UnsupportedOperationException();
                    }

                    @Override
                    public void clear() {
                        ListIsFunction.this.asMap().clear();
                    }

                    @Override
                    public String toString() {
                        return ks.toString();
                    }

                    @Override
                    public int hashCode() {
                        return ks.hashCode();
                    }

                };
            }

            // Tutaj moze cos
            // Nie wiem jak z usuwaniem z values
            @Override
            public Collection<Object> values() {
                return new Collection<Object>() {
                    Collection v = map.values();

                    @Override
                    public int size() {
                        return v.size();
                    }

                    @Override
                    public boolean isEmpty() {
                        return v.isEmpty();
                    }

                    @Override
                    public boolean contains(Object o) {
                        return v.contains(o);
                    }

                    @Override
                    public Iterator<Object> iterator() {
                        return v.iterator();
                    }

                    @Override
                    public Object[] toArray() {
                        return v.toArray();
                    }

                    @Override
                    public Object[] toArray(Object[] a) {
                        return v.toArray(a);
                    }

                    @Override
                    public boolean add(Object e) {
                        throw new UnsupportedOperationException();
                    }

                    @Override
                    public boolean remove(Object o) {
                        throw new UnsupportedOperationException();
                    }

                    @Override
                    public boolean containsAll(Collection<?> c) {
                        return v.containsAll(c);
                    }

                    @Override
                    public boolean addAll(Collection<? extends Object> c) {
                        throw new UnsupportedOperationException();
                    }

                    @Override
                    public boolean removeAll(Collection<?> c) {
                        throw new UnsupportedOperationException();
                    }

                    @Override
                    public boolean retainAll(Collection<?> c) {
                        throw new UnsupportedOperationException();
                    }

                    @Override
                    public void clear() {
                        ListIsFunction.this.asMap().clear();
                    }

                    @Override
                    public String toString() {
                        return v.toString();
                    }

                    @Override
                    public int hashCode() {
                        return v.hashCode();
                    }

                    @Override
                    public boolean equals(Object o) {
                        return v.equals(o);
                    }

                };
            }

            // Nie dziala, jezeli najpierw stworzymy entrySeta, potem dodamy elementy,
            // a potem bedziemy robic iteratorem
            // Tested
            @Override
            public Set<Entry<Integer, Object>> entrySet() {
                return new Set<Entry<Integer, Object>>() {
                    Set<Entry<Integer, Object>> es = map.entrySet();
                    Iterator<Entry<Integer, Object>> it = es.iterator();

                    // Tested
                    @Override
                    public int size() {
                        return es.size();
                    }

                    // Tested
                    @Override
                    public boolean isEmpty() {
                        return es.isEmpty();
                    }

                    @Override
                    public boolean contains(Object o) {
                        return es.contains(o);
                    }

                    // Tested
                    @Override
                    public Iterator<Entry<Integer, Object>> iterator() {
                        return new Iterator<Entry<Integer, Object>>() {

                            // Tested
                            @Override
                            public boolean hasNext() {
                                return it.hasNext();
                            }

                            // Tested
                            @Override
                            public Entry<Integer, Object> next() {
                                return it.next();
                            }

                            // Tested
                            @Override
                            public void remove() {
                                if (!hasNext()) {
                                    ListIsFunction.this.asList().remove(list.size() - 1);
                                } else {
                                    throw new java.lang.IllegalStateException();
                                }
                            }
                        };
                    }

                    @Override
                    public Object[] toArray() {
                        return es.toArray();
                    }

                    @Override
                    public <T> T[] toArray(T[] a) {
                        return es.toArray(a);
                    }

                    @Override
                    public boolean add(Entry<Integer, Object> e) {
                        throw new UnsupportedOperationException();
                    }

                    // Tested
                    @Override
                    public boolean remove(Object o) {
                        if (!es.contains(o)) {
                            return false;
                        }
                        if (o instanceof Map.Entry) {
                            Map.Entry<Integer, Object> e = (Map.Entry<Integer, Object>) o;
                            Object key = e.getKey();
                            Object value = e.getValue();
                            ListIsFunction.this.asMap().remove(key);
                            return true;
                        }
                        return false;
                    }

                    @Override
                    public boolean containsAll(Collection<?> c) {
                        return es.containsAll(c);
                    }

                    @Override
                    public boolean addAll(Collection<? extends Entry<Integer, Object>> c) {
                        throw new UnsupportedOperationException();
                    }

                    // Tutaj
                    @Override
                    public boolean retainAll(Collection<?> c) {
                        throw new UnsupportedOperationException();
                    }

                    // Tutaj
                    @Override
                    public boolean removeAll(Collection<?> c) {
                        throw new UnsupportedOperationException();
                    }

                    // Tested
                    @Override
                    public void clear() {
                        ListIsFunction.this.asMap().clear();
                    }

                    // Tested
                    @Override
                    public String toString() {
                        return es.toString();
                    }

                    @Override
                    public int hashCode() {
                        return es.hashCode();
                    }

                    @Override
                    public boolean equals(Object o) {
                        return es.equals(o);
                    }

                };
            }

            // Tested
            @Override
            public String toString() {
                return map.toString();
            }
        };
    }
}