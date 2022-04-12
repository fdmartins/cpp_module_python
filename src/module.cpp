#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <vector>
#include <Python.h>

// PyInit_cppModuleTest é o nosso "void main()"

using namespace std;

vector<float> listTupleToVector_Float(PyObject* incoming) {
	vector<float> data;
	if (PyTuple_Check(incoming)) {
		for(Py_ssize_t i = 0; i < PyTuple_Size(incoming); i++) {
			PyObject *value = PyTuple_GetItem(incoming, i);
			data.push_back( PyFloat_AsDouble(value) );
		}
	} else {
		if (PyList_Check(incoming)) {
			for(Py_ssize_t i = 0; i < PyList_Size(incoming); i++) {
				PyObject *value = PyList_GetItem(incoming, i);
				data.push_back( PyFloat_AsDouble(value) );
			}
		} else {
			throw logic_error("Passed PyObject pointer was not a list or tuple!");
		}
	}
	return data;
}



static PyObject *method_set_2string(PyObject *self, PyObject *args) 
{
    char *str1, *str2 = NULL;

    /* Parse arguments */
    // s = string, o parse colocara os valores dos parametros em cada variavel: str1, str2
    if(!PyArg_ParseTuple(args, "ss", &str1, &str2)) {
        return NULL;
    }

    //FILE *fp = fopen(filename, "w");
    //bytes_copied = fputs(str, fp);
    //fclose(fp);

    int string_len = strlen(str1) + strlen(str2);

    //return Py_None;
    return PyLong_FromLong(string_len);
}

static PyObject *method_set_list(PyObject *self, PyObject *args) 
{
    PyObject *pList;

    /* Parse arguments */
    // O = object 
    if (!PyArg_ParseTuple(args, "O!", &PyList_Type, &pList)) {
        PyErr_SetString(PyExc_TypeError, "parameter must be a list.");
    }

    // convertemos a lista para vetor de floats
    vector<float> data =  listTupleToVector_Float(pList);

    // mostramos os resultados e somamos.
    float total = 0;
    for(unsigned long i=0; i<data.size(); i++){
        //printf("%f ", data[i]);
        total+= data[i];
    }
    //printf("\n");
    
    //return Py_None;
    return PyLong_FromLong(total);
}

// definidicao dos metodos disponivels no modulo
static PyMethodDef cppModuleTestMethods[] = {
    {"set_2string", method_set_2string, METH_VARARGS, "descricao da funcao"},
    {"set_list", method_set_list, METH_VARARGS, "descricao da funcao"},
    {NULL, NULL, 0, NULL}
};


static struct PyModuleDef cppModuleTestmodule = {
    PyModuleDef_HEAD_INIT,
    "cppModuleTest",
    "Doc Modulo C",
    -1,
    cppModuleTestMethods
};

// nota: PyInit_*** , onde *** precisa ter o mesmo nome do modulo definido em setup.py
PyMODINIT_FUNC PyInit_cppModuleTest(void) {
    return PyModule_Create(&cppModuleTestmodule);
}