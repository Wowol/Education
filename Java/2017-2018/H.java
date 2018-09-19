
//package Satori.H;

import java.lang.reflect.*;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;
import java.util.HashMap;

public class SmartFactory {

    public static class HellNoException extends RuntimeException {

    }

    static void setDefaultValues(HashMap<Class<?>, Object> usedClassess, Object o) {
        usedClassess.put(o.getClass(), o);

        for (Field f : o.getClass().getFields()) {
            Class<?> cl = f.getType();
            try {
                if (!f.getType().isPrimitive() && !f.getType().isArray()) {
                    if (f.get(o) == null) {
                        boolean found = false;

                        for (Class<?> c : usedClassess.keySet()) {
                            if (cl.isAssignableFrom(c)) {
                                f.set(o, usedClassess.get(c));
                                found = true;
                                break;
                            }
                        }
                        if (found)
                            continue;

                        f.set(o, cl.newInstance());
                        usedClassess.put(cl, f.get(o));
                        setDefaultValues(usedClassess, f.get(o));
                    }
                }
            } catch (Exception e) {
                throw new HellNoException();
            }
        }
    }

    public static <T> T fixIt(Class<T> cl, Object obj) {

        ArrayList<Method> objMethods = obj != null ? new ArrayList<>(Arrays.asList(obj.getClass().getMethods())) : null;

        @SuppressWarnings("unchecked")
        T returnObject = (T) Proxy.newProxyInstance(cl.getClassLoader(), new Class[] { cl }, new InvocationHandler() {

            @Override
            public Object invoke(Object proxy, Method method, Object[] args) throws Throwable {
                HashMap<Class<?>, Object> usedClassess = new HashMap<>();
                int argsLength = args == null ? 0 : args.length;
                String methodName = method.getName();
                Class<?>[] classessParameters = method.getParameterTypes();

                /////////////////////////////// PHASE 1

                if (obj != null) {
                    Method lastGoodMethod = null;
                    for (Method m : objMethods) {
                        Class<?>[] objParameters = m.getParameterTypes();
                        int objParametersLength = objParameters == null ? 0 : objParameters.length;

                        if (m.getName() != methodName)
                            continue;

                        if (!method.getReturnType().isAssignableFrom(m.getReturnType()))
                            continue;

                        if (argsLength != objParametersLength)
                            continue;

                        boolean allParametersWork = true;
                        for (int x = 0; x < objParametersLength; x++) {
                            if (!objParameters[x].isAssignableFrom(classessParameters[x])) {
                                allParametersWork = false;
                                break;
                            }
                        }

                        if (!allParametersWork)
                            continue;

                        boolean allGoodException = true;
                        for (int x = 0; x < m.getExceptionTypes().length; x++) {
                            boolean foundOne = false;
                            for (int y = 0; y < method.getExceptionTypes().length; y++) {
                                if (method.getExceptionTypes()[y].isAssignableFrom(m.getExceptionTypes()[x])) {
                                    foundOne = true;
                                    break;
                                }
                            }
                            if (!foundOne) {
                                allGoodException = false;
                                break;
                            }
                        }
                        if (!allGoodException)
                            continue;

                        if (lastGoodMethod != null) {
                            throw new HellNoException();
                        }
                        lastGoodMethod = m;
                    }

                    if (lastGoodMethod != null) {
                        try {
                            return lastGoodMethod.invoke(obj, args);
                        } catch (InvocationTargetException e) {
                            throw e.getCause();
                        }
                    }
                }

                ///////////////////////////////// PHASE 2

                try {
                    if (method.getReturnType().equals(Void.TYPE)) {
                        return null;
                    }
                    Object p = method.getReturnType().newInstance();
                    setDefaultValues(usedClassess, p);
                    return p;
                } catch (Exception e) {
                    throw new HellNoException();
                }

            }
        });
        return returnObject;

    }
}
