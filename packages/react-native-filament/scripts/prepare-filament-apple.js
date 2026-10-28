const { execFileSync } = require('node:child_process')
const crypto = require('node:crypto')
const fs = require('node:fs')
const os = require('node:os')
const path = require('node:path')

const LIBRARIES = [
  'gltfio_core', 'filament', 'backend', 'smol-v', 'ktxreader', 'image', 'basis_transcoder', 'camutils', 'geometry', 'mikktspace',
  'meshoptimizer', 'dracodec', 'uberarchive', 'uberzlib', 'zstd', 'stb', 'filabridge', 'filaflat', 'perfetto', 'abseil', 'utils',
]

function fail(message) {
  throw new Error(`[react-native-filament] ${message}`)
}

function publish(source, target) {
  try {
    fs.renameSync(source, target)
  } catch (error) {
    if (error.code !== 'EEXIST' && error.code !== 'ENOTEMPTY') throw error
    fs.rmSync(source, { recursive: true, force: true })
  }
}

function sha256(file) {
  return crypto.createHash('sha256').update(fs.readFileSync(file)).digest('hex')
}

function fetchVerified(pin, asset, entry) {
  const part = path.join(entry, `archive.${crypto.randomBytes(6).toString('hex')}.part`)
  const local = process.env.RNF_FILAMENT_IOS_ARCHIVE
  if (local) {
    fs.copyFileSync(local, part)
  } else {
    const url = `${process.env.RNF_FILAMENT_BASE_URL ?? pin.baseUrl}/${asset.name}`
    console.log(`[react-native-filament] Downloading ${url}`)
    try {
      execFileSync('curl', ['--fail', '--location', '--silent', '--show-error', '--speed-limit', '1024', '--speed-time', '60', '--output', part, url], { stdio: 'inherit' })
    } catch {
      fs.rmSync(part, { force: true })
      fail(`Downloading ${url} failed. Set RNF_FILAMENT_IOS_ARCHIVE to a local copy or RNF_FILAMENT_BASE_URL to a mirror.`)
    }
  }
  const actual = sha256(part)
  if (actual !== asset.sha256) {
    fs.rmSync(part, { force: true })
    fail(`${local ?? asset.name} has SHA-256 ${actual}, expected ${asset.sha256}. Set RNF_FILAMENT_IOS_ARCHIVE to a verified copy or RNF_FILAMENT_BASE_URL to a mirror.`)
  }
  return part
}

function extractValidated(archive, entry) {
  const listing = execFileSync('tar', ['-tvzf', archive], { encoding: 'utf8', maxBuffer: 64 * 1024 * 1024 })
  for (const line of listing.split('\n').filter(Boolean)) {
    const kind = line[0]
    const name = line.trim().split(/\s+/).pop()
    const inside = name === 'filament/' || name.startsWith('filament/')
    if (!['-', 'd'].includes(kind) || !inside || name.split('/').includes('..')) fail(`Unexpected entry '${line.trim()}' in ${archive}`)
  }
  const tmp = path.join(entry, `dist.${crypto.randomBytes(6).toString('hex')}.tmp`)
  fs.mkdirSync(tmp, { recursive: true })
  execFileSync('tar', ['-xzf', archive, '-C', tmp])
  return tmp
}

function ensureStoreEntry(pin, asset) {
  const entry = path.join(os.homedir(), 'Library', 'Caches', 'react-native-filament', `sha256-${asset.sha256}`)
  const dist = path.join(entry, 'dist')
  if (fs.existsSync(dist)) return dist
  fs.mkdirSync(entry, { recursive: true })
  const archive = path.join(entry, 'archive.tgz')
  if (!fs.existsSync(archive)) publish(fetchVerified(pin, asset, entry), archive)
  const extracted = extractValidated(archive, entry)
  publish(path.join(extracted, 'filament'), dist)
  fs.rmSync(extracted, { recursive: true, force: true })
  return dist
}

/** Vendors the pinned Filament iOS libraries into apple/Filament, where Package.swift links them. */
function prepareFilamentApple(packageDir) {
  const pin = JSON.parse(fs.readFileSync(path.join(packageDir, 'filament.json'), 'utf8'))
  const asset = pin.assets.ios
  const vendored = path.join(packageDir, 'apple', 'Filament')
  const stamp = path.join(vendored, '.sha256')
  if (fs.existsSync(stamp) && fs.readFileSync(stamp, 'utf8').trim() === asset.sha256) return vendored
  const dist = ensureStoreEntry(pin, asset)
  const tmp = `${vendored}.${crypto.randomBytes(6).toString('hex')}.tmp`
  fs.mkdirSync(path.join(tmp, 'lib'), { recursive: true })
  execFileSync('cp', ['-cR', path.join(dist, 'include'), tmp])
  for (const lib of LIBRARIES) execFileSync('cp', ['-cR', path.join(dist, 'lib', `lib${lib}.xcframework`), path.join(tmp, 'lib')])
  fs.writeFileSync(path.join(tmp, '.sha256'), `${asset.sha256}\n`)
  fs.rmSync(vendored, { recursive: true, force: true })
  publish(tmp, vendored)
  return vendored
}

module.exports = { LIBRARIES, prepareFilamentApple }

if (require.main === module) prepareFilamentApple(path.resolve(__dirname, '..'))
