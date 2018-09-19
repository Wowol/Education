//package Satori;

public class PhoneBook {

    public enum NumberFormat {
        DIGITS, HYPHENED
    }

    public enum Content {
        NUMBERS, PHONEBOOKS, UNKNOWN
    }

    Object elements[];
    NumberFormat format;
    int capacity;
    int sizeOfElements = 0;

    public PhoneBook() {
        this(NumberFormat.DIGITS, 10);
    }

    public PhoneBook(NumberFormat format) {
        this(format, 10);
    }

    public PhoneBook(int capacity) {
        this(NumberFormat.DIGITS, capacity);
    }

    public PhoneBook(NumberFormat format, int capacity) {
        if (format == null) {
            format = NumberFormat.DIGITS;
        }
        elements = new Object[capacity + 1];
        this.format = format;
        this.capacity = capacity;
    }

    public String convertToFormat(String number, NumberFormat format) {
        if (format == NumberFormat.DIGITS && number.length() == 9) {
            return number;
        }
        if (format == NumberFormat.HYPHENED && number.length() == 11) {
            return number;
        }

        if (format == NumberFormat.DIGITS) {
            number = number.replaceAll("-", "");
        } else {
            number = new StringBuilder(number).insert(3, "-").insert(7, "-").toString();
        }
        return number;
    }

    Content getContent() {
        if (elements[0] instanceof PhoneBook) {
            return Content.PHONEBOOKS;
        } else if (elements[0] instanceof String) {
            return Content.NUMBERS;
        }
        return Content.UNKNOWN;
    }

    public PhoneBook copyBook() {
        PhoneBook result = new PhoneBook(format, capacity);
        for (int x = 0; x < sizeOfElements; x++) {
            if (getContent() == Content.NUMBERS) {
                result.elements[x] = (String) elements[x];
            } else {
                result.elements[x] = ((PhoneBook) elements[x]).copyBook();
            }
        }
        result.sizeOfElements = sizeOfElements;

        return result;
    }

    public int size() {
        if (getContent() != Content.PHONEBOOKS) {
            return sizeOfElements;
        } else {
            int tempSize = 0;
            for (int x = 0; x < sizeOfElements; x++) {
                PhoneBook temp = (PhoneBook) elements[x];
                tempSize += temp.size();
            }
            return tempSize;
        }
    }

    public int capacity() {
        return capacity;
    }

    public boolean isEmpty() {
        return (sizeOfElements == 0);
    }

    public boolean isFull() {
        return capacity == size();
    }

    private NumberFormat getFormat(String number) {
        if (number == null) {
            return null;
        }
        if (number.length() == 9) {
            if (number.charAt(0) == '0')
                return null;
            for (int x = 0; x < 9; x++) {
                if (!Character.isDigit(number.charAt(x))) {
                    return null;
                }
            }
            return NumberFormat.DIGITS;
        } else if (number.length() == 11) {
            if (number.charAt(0) == '0') {
                return null;
            }
            for (int x = 0; x < 11; x++) {
                if (!Character.isDigit(number.charAt(x))) {
                    if ((x == 3 || x == 7) && number.charAt(x) == '-') {
                        continue;
                    } else {
                        return null;
                    }
                }
            }
            return NumberFormat.HYPHENED;
        }
        return null;
    }

    private boolean checkIfGoodFormat(String number) {
        return getFormat(number) == format;
    }

    private boolean canAddNumber(String number) {
        if (number == null) {
            return false;
        }
        if (getContent() == Content.PHONEBOOKS || size() >= capacity)
            return false;
        return !contains(number);
    }

    private boolean canAddSubBook(PhoneBook pb) {
        if (pb == null) {
            return false;
        }
        if (getContent() == Content.NUMBERS || size() + pb.size() > capacity)
            return false;

        if (sizeOfElements >= 10) {
            return false;
        }

        return !contains(pb);
    }

    public PhoneBook add(String number) {
        if (number == null) {
            return this;
        }
        if (canAddNumber(number) && checkIfGoodFormat(number)) {
            elements[sizeOfElements++] = convertToFormat(number, NumberFormat.DIGITS);
        }
        return this;
    }

    public PhoneBook add(PhoneBook sb) {
        if (sb == null) {
            return this;
        }
        PhoneBook subBook = sb.copyBook();
        if (canAddSubBook(subBook)) {
            elements[sizeOfElements++] = subBook;
        }
        subBook.changeFormat(format);
        return this;
    }

    public void changeFormat(NumberFormat format) {
        if (format == null) {
            return;
        }
        if (this.format == format)
            return;
        this.format = format;

        if (getContent() == Content.PHONEBOOKS) {
            for (int x=0; x<sizeOfElements; x++) {
                ((PhoneBook) elements[x]).changeFormat(format);
            }
        }
    }

    public boolean contains(String number) {
        if (number == null) {
            return false;
        }
        if (getContent() == Content.PHONEBOOKS) {
            for (int x = 0; x < sizeOfElements; x++) {
                if (((PhoneBook) (elements[x])).contains(number))
                    return true;
            }
            return false;
        } else {
            if (getFormat(number) != format) {
                return false;
            }
            return contains((Object) convertToFormat(number, NumberFormat.DIGITS));
        }
    }

    public boolean contains(PhoneBook pb) {
        if (pb == null) {
            return false;
        }
        if (getContent() != Content.PHONEBOOKS) {
            return false;
        }
        NumberFormat oldFormat = pb.format;
        pb.changeFormat(format);
        boolean result = contains((Object) pb);
        pb.changeFormat(oldFormat);
        return result;
    }

    private boolean contains(Object o) {
        if (o == null) {
            return false;
        }
        for (int x = 0; x < sizeOfElements; x++) {
            Object temp = elements[x];
            if (temp.equals(o)) {
                return true;
            }
        }
        return false;
    }

    public boolean elementOf(PhoneBook pb) {
        if (pb == null) {
            return false;
        }
        return pb.contains(this);
    }

    private boolean subsetFunction(PhoneBook pb) {
        if (pb == null) {
            return false;
        }
        if (getContent() == Content.UNKNOWN) {
            return true;
        }

        if (getContent() != pb.getContent()) {
            return false;
        }

        if (size() > pb.size()) {
            return false;
        }
        for (int x = 0; x < sizeOfElements; x++) {
            boolean found = false;
            for (int y = 0; y < pb.sizeOfElements; y++) {
                if (elements[x].equals(pb.elements[y])) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                return false;
            }

        }
        return true;
    }

    public boolean subsetOf(PhoneBook pb) {
        if (pb == null) {
            return false;
        }
        NumberFormat oldFormat = pb.format;
        pb.changeFormat(format);
        boolean result = subsetFunction(pb);
        pb.changeFormat(oldFormat);
        return result;
    }

    public boolean supersetOf(PhoneBook pb) {
        if (pb == null) {
            return false;
        }
        return pb.subsetOf(this);
    }

    public boolean equals(Object obj) {
        if (obj == null)
            return false;
        if (obj.getClass() != getClass())
            return false;
        PhoneBook pb = (PhoneBook) obj;
        return (pb.subsetOf(this) && pb.sizeOfElements == sizeOfElements);
    }

    public String toString() {
        return toString(1);
    }

    public String toString(int level) {
        StringBuilder sb = new StringBuilder();
        sb.append("{\n");
        if (getContent() == Content.NUMBERS) {
            for (int x = 0; x < sizeOfElements; x++) {
                for (int y = 0; y < level; y++) {
                    sb.append("  ");
                }
                sb.append(convertToFormat((String) elements[x], format) + "\n");
            }
        } else if (getContent() == Content.PHONEBOOKS) {
            for (int x = 0; x < sizeOfElements; x++) {
                for (int y = 0; y < level; y++) {
                    sb.append("  ");
                }
                sb.append(((PhoneBook) (elements[x])).toString(level + 1));
            }
        }
        for (int y = 0; y < level - 1; y++) {
            sb.append("  ");
        }
        sb.append("}\n");
        return sb.toString();
    }
}