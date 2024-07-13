import type { Principal } from '@dfinity/principal';
import type { ActorMethod } from '@dfinity/agent';
import type { IDL } from '@dfinity/candid';

export interface Valvula { 'estado' : string }
export interface _SERVICE {
  'abrirValvula' : ActorMethod<[string], boolean>,
  'cerrarValvula' : ActorMethod<[string], boolean>,
  'crearValvula' : ActorMethod<[], undefined>,
  'eliminarValvula' : ActorMethod<[string], boolean>,
  'obtieneValvula' : ActorMethod<[string], [] | [Valvula]>,
  'obtieneValvulas' : ActorMethod<[], Array<[string, Valvula]>>,
}
export declare const idlFactory: IDL.InterfaceFactory;
export declare const init: ({ IDL }: { IDL: IDL }) => IDL.Type[];
