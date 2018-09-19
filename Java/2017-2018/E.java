
//package Satori.E;

import java.util.*;

public class Functions {
    public static <T, S> Function<T, S> constant(S value) throws GenericFunctionsException {
        return new Function<T, S>() {
            @Override
            public int arity() {
                return 0;
            }

            @Override
            public S compute(List<? extends T> args) throws GenericFunctionsException {
                if (args == null) {
                    throw new GenericFunctionsException();
                }

                if (!args.isEmpty())
                    throw new GenericFunctionsException();
                return value;
            }
        };
    }

    public static <T extends S, S> Function<T, S> proj(int n, int k) throws GenericFunctionsException {
        if (k < 0 || k >= n) {
            throw new GenericFunctionsException();
        }
        return new Function<T, S>() {
            @Override
            public int arity() {
                return n;
            }

            @Override
            public S compute(List<? extends T> args) throws GenericFunctionsException {
                if (args == null) {
                    throw new GenericFunctionsException();
                }
                if (args.size() != arity())
                    throw new GenericFunctionsException();
                return args.get(k);
            }
        };
    }

    public static <T, S, V> Function<V, S> compose(Function<? super T, ? extends S> a,
            List<? extends Function<? super V, ? extends T>> tempFunctionsList) throws GenericFunctionsException {

        if (a == null || tempFunctionsList == null) {
            throw new GenericFunctionsException();
        }

        if (a.arity() != tempFunctionsList.size()) {
            throw new GenericFunctionsException();
        }

        return new Function<V, S>() {
            List<Function<? super V, ? extends T>> list = new ArrayList<>();
            {
                for (Function<? super V, ? extends T> f : tempFunctionsList) {
                    if (f.arity() != tempFunctionsList.get(0).arity()) {
                        throw new GenericFunctionsException();
                    }
                    list.add(f);
                }
            }

            @Override
            public int arity() {
                return list.size() > 0 ? list.get(0).arity() : 0;
            }

            @Override
            public S compute(List<? extends V> args) throws GenericFunctionsException {
                if (args == null) {
                    throw new GenericFunctionsException();
                }

                if (args.size() != arity()) {
                    throw new GenericFunctionsException();
                }
                List<T> q = new ArrayList<>();
                for (Function<? super V, ? extends T> f : list) {
                    q.add(f.compute(args));
                }
                return a.compute(q);
            }
        };
    }

}