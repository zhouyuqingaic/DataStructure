cmake_minimum_required(VERSION 3.24)
project(DataStructure C)

set(CMAKE_C_STANDARD 99)

add_executable(
        DataStructure main.c
        01SerialList/dynamicArray/dynamicArray.h
        01SerialList/dynamicArray/dynamicArray.c
        01SerialList/dynamicArray/usingDynamicArray.c
        01SerialList/linkList/usingLinkList.c
        01SerialList/linkList/linkList.c
        01SerialList/linkList/linkList.h
        01SerialList/stackSequence/stackSequence.h
        01SerialList/stackSequence/stackSequence.c
        01SerialList/stackLinkList/stackLinkList.h
        01SerialList/stackLinkList/stackLinkList.c
        01SerialList/stackLinkList/usingStackLinkList.c
        01SerialList/stackSequence/usingStackSequence.c
        01SerialList/queueSequenceByDynamicArray/queueSequenceByDynamicArray.h
        01SerialList/queueSequenceByDynamicArray/queueSequenceByDynamicArray.c
        01SerialList/queueSequenceByDynamicArray/usingQueueSequenceByDynamicArray.c
        01SerialList/queueByLinkList/queueByLinkList.h
        01SerialList/queueByLinkList/queueByLinkList.c
        01SerialList/queueByLinkList/usingQueueByLinkList.c
        02String/stringFixedLength/stringFixedLength.h
        02String/stringFixedLength/stringFixedLength.c
        02String/stringFixedLength/usingStringFixedLength.c
        02String/stringDynamic/stringDynamic.h
        02String/stringDynamic/stringDynamic.c
        02String/stringDynamic/usingStringDynamic.c
        03Matrix/matrixByArray/matrixByArray.h
        03Matrix/matrixByArray/matrixByArray.c
        03Matrix/matrixByArray/usingMatrixByArray.c
        03Matrix/spareMatrixByArray/spareMatrixByArray.h
        03Matrix/spareMatrixByArray/spareMatrixByArray.c
        03Matrix/spareMatrixByArray/usingSpareMatrixByArray.c
        03Matrix/spareMatrixByCrossLink/spareMatrixByCrossLink.h
        03Matrix/spareMatrixByCrossLink/spareMatrixByCrossLink.c
        03Matrix/spareMatrixByCrossLink/usingSpareMatrixByCrossLink.c
        04Tree/binaryTree/binaryTree.h 04Tree/binaryTree/binaryTree.c
        04Tree/binaryTree/usingBinaryTree.c 04Tree/binarySortTree/binarySortTree.h
        04Tree/binarySortTree/binarySortTree.c
        04Tree/binarySortTree/usingBinarySortTree.c
        05Graph/directGraphAdjacencyList/directGraphAdjacencyList.h
        05Graph/directGraphAdjacencyMatrix/directGraphAdjacencyMatrix.h
        05Graph/directGraphAdjacencyMatrix/directGraphAdjacencyMatrix.c
        05Graph/directGraphAdjacencyMatrix/usingDirectGraphAdjacencyMatrix.c
        05Graph/directGraphAdjacencyList/directGraphAdjacencyList.c
        05Graph/directGraphAdjacencyList/usingDirectGraphAdjacencyList.c
        05Graph/undirectGraphAdjacencyMatrix/undirectGraphAdjacencyMatrix.h
        05Graph/undirectGraphAdjacencyMatrix/undirectGraphAdjacencyMatrix.c
        05Graph/undirectGraphAdjacencyMatrix/usingUnDirectGraphAdjacencyMatrix.c
        05Graph/aovGraphAdjacencyList/aovGraphAdjacencyList.h
        05Graph/aovGraphAdjacencyList/aovGraphAdjacencyList.c
        05Graph/aovGraphAdjacencyList/usingAovGraphAdjacencyList.c
        05Graph/aoeGraphAdjacencyList/aoeGraphAdjacencyList.h
        05Graph/aoeGraphAdjacencyList/aoeGraphAdjacencyList.c
        05Graph/aoeGraphAdjacencyList/usingAoeGraphAdjacencyList.c
        06Sort/insertSort/insertSort.h 06Sort/insertSort/insertSort.c
        06Sort/insertSort/usingInsertSort.c 06Sort/swipSort/swipSort.h
        06Sort/swipSort/swipSort.c 06Sort/swipSort/usingSwipSort.c
        06Sort/selectSort/selectSort.h 06Sort/selectSort/selectSort.c
        06Sort/selectSort/usingSelectSort.c 06Sort/mergeSort/mergeSort.h
        06Sort/mergeSort/mergeSort.c 06Sort/mergeSort/usingMergeSort.c
        07Search/hashDict/hashDict.h 07Search/hashDict/hashDict.c 07Search/hashDict/usingHashDict.c 07Search/bstDict/bstDict.h 07Search/bstDict/bstDict.c 07Search/bstDict/usingBstDict.c)
