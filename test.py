# nome do nosso modulo
import cppModuleTest as mymodule

# descricao e nome do modulo, definido em /src/module.cpp em PyModuleDef.
print("Sobre este modulo:", mymodule.__doc__)
print("Nome deste modulo:", mymodule.__name__)

# funcao que envia uma lista de numeros para o modulo em C++
ret = mymodule.set_list([1, 2, 3])
print("Total soma da lista:", ret)

# funcao que envia 2 strings para o modulo em C++
ret = mymodule.set_2string("String1", "abc")
print("Comprimento das 2 strings concatenadas: ", ret)

