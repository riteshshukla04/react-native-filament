import { PhysicsFactory } from './specs/PhysicsFactory.nitro'

/** Creates physics worlds with `Physics.createWorld(engine, options)` on the Engine's render thread. */
export const Physics = new PhysicsFactory()
