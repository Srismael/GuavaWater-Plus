export const idlFactory = ({ IDL }) => {
  const Valvula = IDL.Record({ 'estado' : IDL.Text });
  return IDL.Service({
    'abrirValvula' : IDL.Func([IDL.Text], [IDL.Bool], []),
    'cerrarValvula' : IDL.Func([IDL.Text], [IDL.Bool], []),
    'crearValvula' : IDL.Func([], [], []),
    'eliminarValvula' : IDL.Func([IDL.Text], [IDL.Bool], []),
    'obtieneValvula' : IDL.Func([IDL.Text], [IDL.Opt(Valvula)], ['query']),
    'obtieneValvulas' : IDL.Func(
        [],
        [IDL.Vec(IDL.Tuple(IDL.Text, Valvula))],
        ['query'],
      ),
  });
};
export const init = ({ IDL }) => { return []; };
