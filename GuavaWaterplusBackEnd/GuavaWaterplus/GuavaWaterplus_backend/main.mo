import HashMap "mo:base/HashMap";
import Iter "mo:base/Iter";
import Nat32 "mo:base/Nat32";
import Text "mo:base/Text";
import Principal "mo:base/Principal";
import Debug "mo:base/Debug";

actor Valvulas {
  type Valvula = {
    estado: Text;
  };

  type valvulaID = Nat32;
  stable var valvulaID: valvulaID = 0;

  let listaValvulas = HashMap.HashMap<Text, Valvula>(0, Text.equal, Text.hash);

  private func generaValvulaID() : Nat32 {
    valvulaID += 1;
    return valvulaID;
  };



  public shared (msg) func crearValvula() : async () {
    let valvula = {estado="cerrada"};

    listaValvulas.put(Nat32.toText(generaValvulaID()), valvula);
    Debug.print("Nueva válvula creada ID: " # Nat32.toText(valvulaID));
    return ();
  };

  public query func obtieneValvulas() : async [(Text, Valvula)] {
    let valvulaIter : Iter.Iter<(Text, Valvula)> = listaValvulas.entries();
    let valvulaArray : [(Text, Valvula)] = Iter.toArray(valvulaIter);
    Debug.print("Válvulas ");

    return valvulaArray;
  };

  public query func obtieneValvula(id: Text) : async ?Valvula {
    let valvula: ?Valvula = listaValvulas.get(id);
    return valvula;
  };

 public shared (msg) func abrirValvula(id: Text, horaApertura: Text) : async Bool {
    let valvula = listaValvulas.get(id);

    switch (valvula) {
        case (null) {
            return false;
        };
        case (?valvulaActual) {
            let nuevaValvula = {
                estado = "abierta";
                horaApertura = horaApertura;
            };
            listaValvulas.put(id, nuevaValvula);
            Debug.print("Válvula abierta: " # id);
            return true;
        };
    };
};



  public shared (msg) func cerrarValvula(id: Text, horaCierre: Text) : async Bool {
    let valvula: ?Valvula = listaValvulas.get(id);

    switch (valvula) {
        case (null) {
            return false;
        };
        case (?valvulaActual) {
            let nuevaValvula = {
                estado = "cerrada";
                horaCierre = horaCierre;
            };
            listaValvulas.put(id, nuevaValvula);
            Debug.print("Válvula cerrada: " # id);
            return true;
        };
    };
};


  public func eliminarValvula(id: Text) : async Bool {
    let valvula : ?Valvula = listaValvulas.get(id);
    switch (valvula) {
      case (null) {
        return false;
      };
      case (_) {
        ignore listaValvulas.remove(id);
        Debug.print("Válvula eliminada: " # id);
        return true;
      };
    };
  };
};