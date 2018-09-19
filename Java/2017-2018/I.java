
//package Satori.I;

import java.util.HashMap;
import java.util.Map;
import java.util.ArrayList;
import java.util.concurrent.locks.ReentrantLock;

public class Locker {
    public static class DeadlockException extends RuntimeException {

    }

    HashMap<Object, ArrayList<Object>> graph = new HashMap<>();
    HashMap<Object, Boolean> used = new HashMap<>();

    public Lock getLock() {
        return new Lock();
    }

    private boolean checkCycle(Object current, Object previous) {
        synchronized (Locker.this) {
            used.put(current, true);
            for (Object o : graph.get(current)) {
                if (o == previous) {
                    continue;
                }
                if (used.get(o) != null && used.get(o) == true) {
                    return true;
                }
                used.put(o, true);
                return checkCycle(o, current);
            }
            return false;
        }

    }

    class Lock {
        private ReentrantLock reentrantLock = new ReentrantLock();

        Lock() {
            synchronized (Locker.this) {
                graph.put(this, new ArrayList<Object>());
            }
        }

        public void lock() throws InterruptedException {
            synchronized (Locker.this) {

                if (graph.get(Thread.currentThread()) == null) {
                    graph.put(Thread.currentThread(), new ArrayList<Object>());
                }

                for (Map.Entry<Object, Boolean> o : used.entrySet()) {
                    o.setValue(false);
                }

                graph.get(this).add(Thread.currentThread());
                graph.get(Thread.currentThread()).add(this);

                if (checkCycle(this, null)) {
                    graph.get(this).remove(Thread.currentThread());
                    graph.get(Thread.currentThread()).remove(this);

                    throw new DeadlockException();
                }
            }
            reentrantLock.lockInterruptibly();
        }

        public synchronized void unlock() {
            reentrantLock.unlock();

            synchronized (Locker.this) {
                graph.get(this).remove(Thread.currentThread());
                graph.get(Thread.currentThread()).remove(this);
            }
        }
    }
}