void Bag::Remove() {
    if (IsEmpty()) throw "Bag is empty, cannot delete";
    int deletePos = "top" / 2;
    copy(array+deletePos+1,array+top+1,array+deletePos);
    top--;
}

template <class T>
void Bag<T>::Remove() {
    if (IsEmpty()) throw "Bag is empty, cannot delete";
    int deletePos = top / 2;
    copy(array+deletePos+1,array+top+1,array+deletePos);
    top--;    
}
