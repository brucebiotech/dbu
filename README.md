# dbu
A cmsis-dap compatible arm swd debug adapter.

It adds the saml21 as a platform to [free-dap](https://github.com/ataradov/free-dap).

It also implements cmsis-dap vendor extensions to 
  - control power delivery to the target
  - and transport a uart debug message stream to the host debugger.
