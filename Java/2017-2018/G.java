//package Satori;

import java.util.Arrays;
import java.util.SortedMap;
import java.util.function.IntUnaryOperator;
import java.util.function.ToIntFunction;

@FunctionalInterface
interface VarIntFunction extends ToIntFunction<int[]> {

    default int apply(int... args) {
        if (args == null)
            throw new IllegalArgumentException();
        return applyAsInt(args);
    }

    default VarIntFunction applyPartial(int... partialArgs) {

	if (partialArgs == null)
	    throw new IllegalArgumentException();

        if (partialArgs.length == 0) {
            return this;
        }
        return args -> {
	   if (args == null)
            throw new IllegalArgumentException();

            int[] temp = new int[args.length + partialArgs.length];
            for (int x = 0; x < partialArgs.length; x++) {
                temp[x] = partialArgs[x];
            }
            for (int x = 0; x < args.length; x++) {
                temp[x + partialArgs.length] = args[x];
            }
            return apply(temp);
        };
    }

    default IntUnaryOperator unary() {
        return arg -> {
            return apply(arg);
        };
    }

    default VarIntFunction orderArgs(int... argsOrder) {
        if (argsOrder == null) {
            throw new IllegalArgumentException();
        }

        if (argsOrder.length == 0) {
            throw new IllegalArgumentException();
        }
        int sorted[] = new int[argsOrder.length];
        System.arraycopy(argsOrder, 0, sorted, 0, argsOrder.length);
        Arrays.sort(sorted);
        for (int x=0; x<argsOrder.length; x++) {
            if (sorted[x] != x+1)
                 throw new IllegalArgumentException();
        }

        return args -> {
	    if (args == null)
            	throw new IllegalArgumentException();

            if (args.length != argsOrder.length) {
                throw new IllegalArgumentException();
            }


            int[] temp = new int[args.length];
            for (int x = 0; x < argsOrder.length; x++) {
                temp[argsOrder[x] - 1] = args[x];
            }
            return applyAsInt(temp);
        };
    }

    default VarIntFunction checkArgs(int expectedArity) {
	if (expectedArity<0)
		throw new IllegalArgumentException();
	return args -> {
	    if (args == null)
            	throw new IllegalArgumentException();

            if (expectedArity != args.length) {
                throw new IllegalArgumentException();
            }
            return apply(args);
        };
    }
}
